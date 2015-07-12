#include <vector>
#include <sstream>
#include <iosfwd>
#include <streambuf>
#include "Server.h"
#include "defines.h"
#include "ClientsQueue.h"

void Server::run()
{
	this->handlers.reserve(this->handlers_count);
	for(auto i = 0; i<handlers_count; i++)
	{
		auto handler = std::make_shared<Handler>(this);
		this->handlers.push_back(handler);
		handler->start();
	}

	LOG(INFO) << "Handlers started " << this->handlers.size();

	std::stringstream ports_string;
	bool comma = false;
	for(auto &port: this->ports)
	{
		auto connector = std::make_shared<Connector>(port);
		this->connectors.push_back(connector);
		connector->start();

		if(comma)
			ports_string << ',';
		ports_string << port;
		comma = true;
	}

	LOG(INFO) << "Connectors started " << this->connectors.size() << ": " << ports_string.str();

	this->sigint.set<&Server::on_terminate_signal>();
	this->sigint.start(SIGINT);

	this->sigterm.set<&Server::on_terminate_signal>();
	this->sigterm.start(SIGTERM);

	this->sigkill.set<Server::on_terminate_signal>();
	this->sigkill.start(SIGKILL);

	this->loop.run(0);

	this->sigint.stop();
	this->sigterm.stop();
	this->sigkill.stop();

	LOG(INFO) << "Connectors stop pending";

	for(auto &iter: this->connectors)
		iter->stop();

	LOG(INFO) << "Connectors stopped";
	LOG(INFO) << "Handlers stop pending";

	for(auto &iter: this->handlers)
		iter->stop_signal();

	clients_queue()->stop_notify();

	for(int i = 0; i < 100; i++)
		clients_queue()->stop_notify();

	for(auto &iter: this->handlers)
		iter->stop();

	LOG(INFO) << "Handlers stopped";

	this->connectors.clear();
	this->handlers.clear();

	ClientsQueue::delete_instance();

	LOG(INFO) << "Connectors and handlers removed";
	LOG(INFO) << "Gracefull exit";
}

void Server::set_ports(ports_t ports)
{
	this->ports = ports;
}

void Server::set_text(const std::string& text)
{
	if (text.empty())
		this->text = DEFAULT_TEXT;
	else
		this->text = text;

	LOG(INFO) << "Response text: \"" << this->text << "\"";
}

void Server::set_handlers(uint16_t count)
{
	this->handlers_count = count;
}

const std::string* Server::get_text()
{
	return &this->text;
}

void Server::on_terminate_signal(ev::sig& signal, int)
{
	signal.stop();
	signal.loop.break_loop(ev::ALL);
	LOG(INFO) << "Terminate signal";
}


