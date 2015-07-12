#include "ClientsQueue.h"
#include "defines.h"

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
		LOG(INFO) << "EXCEPTIOn";
		result = -1;
	}

	return result;
}

void ClientsQueue::stop_notify()
{
	long int size = 0;
	while(this->queue.size() <= 10000)
	{
		LOG(INFO) << "Queue size " << size;
		this->push(-1);

	}

	//this->queue.abort();
}
