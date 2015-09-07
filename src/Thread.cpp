#include "Thread.h"
#include "defines.h"

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

void Thread::detach()
{
	this->thread.detach();
}