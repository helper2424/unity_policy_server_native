#include "EvThread.h"
#include "defines.h"

EvThread::EvThread():ev_loop_flags(0)
{
	LOG(INFO) << "Thread " << this->thread.get_id() << " created";
}

EvThread::~EvThread()
{
	LOG(INFO) << "Thread destroyed";
}

void EvThread::run()
{
	this->loop = new ev::dynamic_loop(this->ev_loop_flags);
	this->init();

	this->stopper.set(*this->loop);
	this->stopper.set<EvThread, &EvThread::stop_handler>(this);
	this->stopper.start();

	LOG(INFO) << "Thread " << this->thread.get_id() << " started";

	this->loop->run(0);

	LOG(INFO) << "Thread " << this->thread.get_id() << " start finalized";

	this->finalize();

	LOG(INFO) << "Thread " << this->thread.get_id() << " finalized";
}

void EvThread::stop()
{
	this->stopper.send();
	Thread::stop();
}

void EvThread::stop_handler()
{
	this->on_stop();

	this->stopper.stop();
	this->loop->break_loop(ev::ALL);
}



