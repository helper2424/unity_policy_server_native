#pragma once

#include <ev++.h>
#include <thread>

class Thread
{
public:
	typedef std::thread thread_t;
	Thread();
	virtual ~Thread();
	virtual void start();
	void stop();
protected:
	thread_t thread;

	virtual void init() = 0;
	virtual void on_stop() = 0;
	virtual void finalize() = 0;
	virtual void run() = 0;
private:
	Thread(const Thread &) = delete;
	void operator=(const Thread &) = delete;
};
