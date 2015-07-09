#include "ClientsQueue.h"

#include <mutex>

ClientsQueue *ClientsQueue::instance = nullptr;

ClientsQueue::ClientsQueue()
{
}

ClientsQueue* ClientsQueue::get_instance()
{
	if(ClientsQueue::instance == nullptr)
	{
		ClientsQueue::instance = new ClientsQueue;
	}

	return ClientsQueue::instance;
}

void ClientsQueue::push(int client)
{
	this->queue.enqueue(client);
	//this->cv.notify_one();
}

int ClientsQueue::pop()
{
	int result;

	this->queue.wait_dequeue(result);
//	std::unique_lock<mutex_t> lock(this->mutex);
//	this->cv.wait(lock, [this, result]() -> bool { return this->queue.try_dequeue(result); } );

	return result;
}

void ClientsQueue::stop_notify(size_t handlers_count)
{
	for(size_t i = 0; i<handlers_count; i++)
		this->queue.enqueue(-1);
}
