#pragma once

#include "blockingconcurrentqueue.h"
#include <condition_variable>
#include <mutex>

class ClientsQueue
{
public:
	typedef std::mutex mutex_t;
	typedef std::condition_variable cv_t;

	static ClientsQueue *get_instance();
	void push(int);
	int pop();
	void stop_notify();
private:

	static ClientsQueue *instance;
	ClientsQueue();
	ClientsQueue(const ClientsQueue &) = delete;
	void operator=(const ClientsQueue &) = delete;

	moodycamel::BlockingConcurrentQueue<int> queue;
	mutex_t mutex;
	cv_t cv;
};

inline ClientsQueue* clients_queue()
{
	return ClientsQueue::get_instance();
}
