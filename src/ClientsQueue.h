#pragma once

#include "defines.h"
#include <tbb/concurrent_queue.h>
#include <atomic>
#include <mutex>

class ClientsQueue
{
public:
	static ClientsQueue *get_instance();
	static void delete_instance();
	void push(int);
	int pop();
	void stop();
private:

	static ClientsQueue* instance;
	static std::mutex create_mutex;
	ClientsQueue();
	~ClientsQueue();
	ClientsQueue(const ClientsQueue &) = delete;
	void operator=(const ClientsQueue &) = delete;

	tbb::concurrent_bounded_queue<int> queue;
};

inline ClientsQueue* clients_queue()
{
	return ClientsQueue::get_instance();
}
