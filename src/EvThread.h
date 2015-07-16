#pragma once

#include "Thread.h"
#include <ev++.h>

class EvThread : public Thread
{
public:
	EvThread();
	virtual ~EvThread();
	virtual void stop();
protected:
	unsigned int ev_loop_flags;
	ev::dynamic_loop *loop;
	ev::async stopper;

	virtual void init() = 0;
	virtual void on_stop() = 0;
	virtual void finalize() = 0;
	void stop_handler();
	virtual void run();
};
