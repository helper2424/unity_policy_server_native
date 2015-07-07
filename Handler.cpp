#include "Handler.h"
#include "ClientsQueue.h"

#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "easylogging++.h"

Handler::Handler():Thread(), is_run(true)
{
}

void Handler::stop()
{
	this->is_run = false;
	Thread::stop();
}

void Handler::stop_signal()
{
	this->is_run = false;
}

void Handler::init()
{

}

void Handler::on_stop()
{

}

void Handler::run()
{
	while(this->is_run)
	{

		int socket_fd = clients_queue()->pop();
		this->handle(socket_fd);
	}
}

void Handler::finalize()
{

}

void Handler::handle(int socket)
{
	LOG(INFO) << "handle socket " << socket;
	if(socket < 0)
		return;

	const char * data = "<?xml version=\"1.0\"?>\n<cross-domain-policy>\n  <allow-access-from domain=\"*\" to-ports=\"*\"/>\n</cross-domain-policy>";
	send(socket, (void*)data, sizeof(char) * strlen(data), 0);
	close(socket);

//	char ip_address[INET_ADDRSTRLEN];
//	inet_ntop(AF_INET, &(client_addr.sin_addr), ip_address, INET_ADDRSTRLEN);
//	LOG(INFO) << "Handle request from " << ip_address << " port " << this->port;
}

