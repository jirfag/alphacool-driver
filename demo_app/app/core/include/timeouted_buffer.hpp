#ifndef _TIMEOUTED_BUFFER_HPP_
#define _TIMEOUTED_BUFFER_HPP_

#include <mutex>
#include <vector>
#include <condition_variable>

namespace LcdApp
{
	template <class T>
	class TimeoutedBuffer
	{
	private:
		std::vector<T> buffer_;
		size_t count_, capacity_;
		size_t front_, rear_;

		std::mutex lock_;
		std::condition_variable not_full_, not_empty_;

	public:
		TimeoutedBuffer(size_t capacity) : buffer_(capacity), count_(0), capacity_(capacity), front_(0), rear_(0)
		{ }

		void push(T data)
		{
			std::unique_lock<std::mutex> l(lock_);

			not_full_.wait(l, [this](){ return this->count_ != this->capacity_; });

			buffer_[rear_] = data;
			rear_ = (rear_ + 1) % capacity_;
			++count_;

			not_empty_.notify_one();
		}

		bool pop(std::chrono::milliseconds timeout, T &data)
		{
			std::unique_lock<std::mutex> l(lock_);

			while (!count_) {
				if (not_empty_.wait_for(l, timeout) == std::cv_status::timeout)
					return false;
			}

			data = buffer_[front_];
			front_ = (front_ + 1) % capacity_;
			--count_;

			not_full_.notify_one();

			return true;
		}
	};
}

#endif

