#include "Thread.h"
#include "easylogging++.h"

Thread::Thread()
{
}

Thread::~Thread()
{
	LOG(INFO) << "Thread destroyed";
}

void Thread::start()
{
	this->thread = thread_t(&Thread::run, this);
}

void Thread::stop()
{
	this->thread.join();
}



