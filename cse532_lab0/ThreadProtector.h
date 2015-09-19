#include <string>
#include <thread>
#include <vector>
#include <algorithm>

class ThreadProtector
{
public:
	ThreadProtector(){};
	~ThreadProtector()
	{
		std::for_each(thread_vec.begin(), thread_vec.end(), [](std::thread & t){if (t.joinable()){ t.join(); } });
	}
	ThreadProtector & operator<<(std::thread & t)
	{
		thread_vec.push_back(std::move(t));
		return *this;
	}
	void operator()()
	{
		std::for_each(thread_vec.begin(), thread_vec.end(), [](std::thread & t){if (t.joinable()){ t.join(); } });
	}
	ThreadProtector(ThreadProtector const&) = delete;
	ThreadProtector & operator=(ThreadProtector const&) = delete;
private:
	std::vector<std::thread> thread_vec;
};
