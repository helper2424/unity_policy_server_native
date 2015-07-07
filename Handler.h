#pragma once

#include "Thread.h"
#include <ev++.h>
#include <atomic>

class Handler : public Thread
{
public:
	Handler();
	virtual void stop();
	void stop_signal();
protected:
	virtual void init();
	virtual void finalize();
	virtual void on_stop();
	virtual void run();
	void handle(int socket);
private:
	std::atomic<bool> is_run;
};
