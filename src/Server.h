#pragma once

#include <ev++.h>
#include <unordered_set>
#include <vector>
#include <memory>

#include "Connector.h"
#include "Handler.h"

#define DEFAULT_TEXT "<?xml version=\"1.0\"?>\n<cross-domain-policy>\n  <allow-access-from domain=\"*\" to-ports=\"*\"/>\n</cross-domain-policy>"

class Server {
public:
	typedef std::vector<std::shared_ptr<Connector>> connectors_t;
	typedef std::vector<std::shared_ptr<Handler>> handlers_t;
	typedef std::unordered_set<uint16_t> ports_t;

	void run();
	void set_ports(ports_t);
	void set_text(const std::string&);
	void set_handlers(uint16_t);
	const std::string* get_text();
protected:
	ev::default_loop loop;
	ev::sig sigint;
	ev::sig sigkill;
	ev::sig sigterm;
	connectors_t connectors;
	handlers_t handlers;
	ports_t ports;
	std::string text;
	uint16_t handlers_count;

	static void on_terminate_signal(ev::sig& w, int revents);
};
