#include "ClientsQueue.h"
#include "defines.h"
#include <atomic>

ClientsQueue* ClientsQueue::instance = nullptr;
std::mutex ClientsQueue::create_mutex;

ClientsQueue::ClientsQueue()
{
}

ClientsQueue::~ClientsQueue()
{
	this->queue.abort();
	this->queue.clear();
}

ClientsQueue* ClientsQueue::get_instance()
{
	if(ClientsQueue::instance == nullptr)
	{
		std::lock_guard<std::mutex> lock(create_mutex);

		if(ClientsQueue::instance != nullptr)
			return ClientsQueue::instance;

		ClientsQueue::instance = new ClientsQueue;
	}

	return ClientsQueue::instance;
}

void ClientsQueue::delete_instance()
{
	std::lock_guard<std::mutex> lock(create_mutex);

	delete ClientsQueue::instance;
	ClientsQueue::instance = nullptr;
}

void ClientsQueue::push(int client)
{
	if(!this->queue.try_push(client))
		LOG(WARNING) << "Can't push socket " << client << " to queue";
}

int ClientsQueue::pop()
{
	int result;

	try
	{
		this->queue.pop(result);
	}
	catch(...)
	{
		result = -1;
	}

	return result;
}

void ClientsQueue::stop_notify()
{
	this->queue.abort();
}
