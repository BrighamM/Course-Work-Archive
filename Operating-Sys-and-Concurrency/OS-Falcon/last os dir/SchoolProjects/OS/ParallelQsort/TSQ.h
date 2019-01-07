#ifndef TSQ_
#define TSQ_

#include <mutex>
#include <queue>

template<typename T>
class TSQ
{
	public:
		void enqueue(T t)
		{
			std::lock_guard<std::mutex> l(m);
			q.push(t);
		}

		//template<typename Ts..>
		//void emplace(..Ts args){enqueue(T(..args));}

		T dequeue()
		{
			std::lock_guard<std::mutex> l(m);
			auto res = q.front();
			q.pop();
			return res;
		}

		bool try_dequeue(T& res)
		{
			std::lock_guard<std::mutex> l(m);
			if(q.empty()) 
			{
				return false;
			}
			res = q.front();
			q.pop();
			return true;
		}

		bool isEmpty()
		{
			return q.empty();
		}

	private: 
		std::mutex m;
		std::queue<T> q;
};

#endif
