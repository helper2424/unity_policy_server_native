#include "Handler.h"
#include "ClientsQueue.h"

#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "defines.h"
#include "Server.h"

Handler::Handler(Server *server):Thread(), server(server), is_run(true)
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
	LOG(INFO) << "Handler with thread id " << this->thread.get_id() << " started";

	while(this->is_run)
	{
		int socket_fd = clients_queue()->pop();
		this->handle(socket_fd);
	}

	LOG(INFO) << "Handler with thread id " << this->thread.get_id() << " stopped";
}

void Handler::finalize()
{

}

void Handler::handle(int socket)
{
	if(socket < 0)
		return;

	const char *data = this->server->get_text()->c_str();
	send(socket, (void*)data, sizeof(char) * strlen(data), 0);
	close(socket);
}

