#include "Server.h"
#include <vector>
#include <boost/program_options.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include "defines.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;

int main(int argc, char** argv)
{
	namespace po = boost::program_options;
	typedef vector<uint16_t> ports_params_t;

	el::Configurations log_conf;
	log_conf.setToDefault();

	stringstream usage;
	po::variables_map vm;
	uint16_t handlers_count = 0;
	uint32_t log_file_size = 2097152; // 2 MB by default
	std::string log_file = "/var/log/unity_policy_server/policy.log";

	usage << "Usage: " << argv[0] << " [ -h | -d [-c <handlers_count>] [-p <port>]... [-x <your_xml> | -f <path_to_xml>] [-s <log_file_size>] [-l <path to log file>]] \n" ;

	po::options_description desc(usage.str().c_str());
	desc.add_options()
	  ("help,h", "Print help messages")
	  ("xml,x", po::value<std::string>(), "Xml for respondong to requests")
	  ("file,f", po::value<std::string>(), "Path to xml with policy")
	  ("ports,p", po::value<ports_params_t>(), "Ports to listen requests, by default 843 port used")
	  ("daemon,d", "Use daemon function to detach pipes and daemonize server")
	  ("count,c", po::value<uint16_t>(), "Handlers count. One handler - one thread.")
	  ("log,l", po::value<std::string>(), "Log file path")
	  ("log_size,s", po::value<uint32_t>(), "Log file size in bytes");

	try
	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}
	catch (po::error &e)
	{
		LOG(INFO) << desc;
		abort();
	}

	if (vm.count("help"))
	{
		LOG(INFO) << desc;
		return 0;
	}

	if (vm.count("log"))
		log_file = vm["log"].as<string>();

	

	if (vm.count("daemon"))
	{
		if(daemon(1, 0) < 0)
			LOG(ERROR) << "Can't fork to daemon mode";
	}

	if (vm.count("log_size"))
		log_file_size = vm["log_size"].as<uint32_t>();

	ports_params_t ports_params = {{ 843 }};
	string text;

	if (vm.count("xml"))
	{
		text = vm["xml"].as<string>();
		LOG(INFO) << "Load policy xml from params \"" << text << "\"";
	}
	else if (vm.count("file"))
	{
		string file_path = vm["file"].as<string>();
		ifstream file;
		file.open(file_path);

		if(!file.is_open())
			LOG(FATAL) << desc << "\n" << "Can't open file " << file_path;

		stringstream text_stream;
		string buffer;
		int i = 0;

		while (getline (file, buffer))
		{
			if (i != 0)
				text_stream << std::endl;

			text_stream << buffer;
			i++;
		}

		text = text_stream.str();

		LOG(INFO) << "Load policy xml from file " << file_path << " : "
			<< "\"" << text << "\"";

		file.close();
	}

	if(text.empty())
		LOG(WARNING) << "Your xml is empty";

	if (vm.count("ports"))
		ports_params = vm["ports"].as<ports_params_t>();

	Server::ports_t ports;

	for(auto &port: ports_params)
		ports.insert(port);

	if(vm.count("count"))
		handlers_count = vm["count"].as<uint16_t>();

	if(handlers_count == 0)
		handlers_count = 2;

	log_conf.setGlobally(el::ConfigurationType::Filename, log_file.c_str());
	stringstream buffer;
	buffer << log_file_size;
	log_conf.setGlobally(el::ConfigurationType::MaxLogFileSize, buffer.str());
	el::Loggers::reconfigureLogger("default", log_conf);

	Server server;
	server.set_ports(move(ports));
	server.set_text(text);
	server.set_handlers(handlers_count);
	server.run();

	return 0;
}

