#pragma once

#include "blockingconcurrentqueue.h"

class ClientsQueue
{
public:
	static ClientsQueue *get_instance();
	void push(int);
	int pop();
	void stop_notify(size_t handlers_count);
private:

	static ClientsQueue *instance;
	ClientsQueue();
	ClientsQueue(const ClientsQueue &) = delete;
	void operator=(const ClientsQueue &) = delete;

	moodycamel::BlockingConcurrentQueue<int> queue;
};

inline ClientsQueue* clients_queue()
{
	return ClientsQueue::get_instance();
}
