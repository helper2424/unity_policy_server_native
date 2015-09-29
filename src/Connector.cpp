#include "Connector.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include <netinet/tcp.h>
#include <string.h>
#include "defines.h"
#include "ClientsQueue.h"

Connector::Connector(uint16_t port):port(port), handled_clients(0)
{
	ev_loop_flags |= EVBACKEND_EPOLL;
}

void Connector::init()
{
	this->socket_d = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	int buf = 1;

	if(this->socket_d < 0)
	{
		LOG(ERROR) << "Can't create socket for connection with port " << this->port;
		return;
	}

	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_family = AF_INET;
	address.sin_port = htons(this->port);

	if(setsockopt(this->socket_d, IPPROTO_TCP, TCP_NODELAY, &buf, sizeof(this->socket_d)) == -1)
		LOG(ERROR) << "Can't set socket option TCP_NODELAY with port " << this->port;

	if(setsockopt(this->socket_d, SOL_SOCKET, SO_REUSEADDR, &buf, sizeof(this->socket_d)) == -1)
		LOG(ERROR) << "Can't set socket option SO_REUSEADDR with port " << this->port;

	if(bind(socket_d, (struct sockaddr *)&address, sizeof(address)))
		LOG(ERROR) << "Can't bind address 0.0.0.0:" << this->port;

	listen(socket_d, 5);

	this->connect_watcher.set(*this->loop);
	this->connect_watcher.set<Connector, &Connector::connnect>(this);
	this->connect_watcher.set(socket_d, EV_READ);
	this->connect_watcher.start();

	this->reporter.set(*this->loop);
	this->reporter.set<Connector, &Connector::report>(this);
	this->reporter.start(0, REPORT_TIMEOUT);
}

void Connector::finalize()
{
	if (this->socket_d > 0)
	{
		shutdown(this->socket_d, 2);
		close(this->socket_d);
	}
}

void Connector::on_stop()
{
	this->connect_watcher.stop();
	this->reporter.stop();
}


void Connector::connnect(ev::io& connect_event, int )
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_sd;

	// Accept client request
	client_sd = accept(connect_event.fd, (struct sockaddr *)&client_addr, &client_len);

	clients_queue()->push(client_sd);

	this->handled_clients++;
}

void Connector::report()
{
	uint64_t clients_count = this->handled_clients;

	if (clients_count > 0)
	{
		this->handled_clients = 0;

		LOG(INFO) << "Handled " <<  clients_count << " clients by " << this->port << " port";
	}
}
