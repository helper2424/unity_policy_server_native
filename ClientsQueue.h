#pragma once

#include "defines.h"
#include <tbb/concurrent_queue.h>

class ClientsQueue
{
public:
	static ClientsQueue *get_instance();
	void push(int);
	int pop();
	void stop_notify();
private:

	static ClientsQueue *instance;
	ClientsQueue();
	ClientsQueue(const ClientsQueue &) = delete;
	void operator=(const ClientsQueue &) = delete;

	tbb::concurrent_bounded_queue<int> queue;
};

inline ClientsQueue* clients_queue()
{
	return ClientsQueue::get_instance();
}
