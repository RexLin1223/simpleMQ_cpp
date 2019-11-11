#pragma once
#include <list>
#include <vector>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace queue {

	template<typename T>
	class LockedList {
		boost::shared_mutex mutex_;
		std::list<T> list_;
	public:
		LockedList() {}
		virtual ~LockedList() {}

		// Careful about issue of race condition
		std::list<T>& get() {
			return this->list_;
		}

		void push(const T& obj) {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			list_.emplace_back(obj);
		}

		void push(T&& obj) {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			list_.emplace_back(std::move(obj));
		}

		void consume_one() {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			if (list_.size() > 0) {
				list_.pop_front();
			}
		}

		void consume_all() {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			list_.clear();
		}

		T fetch() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			if (list_.empty()) return T();

			T obj = std::move(list_.front());
			list_.pop_front();
			return obj;
		}

		T& peek() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return list_.front();
		}

		size_t size() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return list_.size();
		}

		bool empty() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return 0 == list_.size();
		}
	};

	template<typename T>
	class LockedVector {
		boost::shared_mutex mutex_;
		std::vector<T> vector_;
	public:
		LockedVector() {}
		virtual ~LockedVector() {}

		// Careful about issue of race condition
		std::vector<T>& get() {
			return this->vector_;
		}

		void push(const T& obj) {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			vector_.emplace_back(obj);
		}

		void push(T&& obj) {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			vector_.emplace_back(std::move(obj));
		}

		void consume_one() {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			if (vector_.size() > 0) {
				vector_.pop_front();
			}
		}

		void consume_all() {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			vector_.clear();
		}

		T fetch() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			if (vector_.empty()) return T();

			T obj = std::move(vector_.front());
			vector_.pop_front();
			return obj;
		}

		T& peek() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return vector_.front();
		}

		size_t size() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return vector_.size();
		}

		bool empty() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return 0 == vector_.size();
		}
	};

	template<typename T1, typename T2>
	class LockedMap {
		boost::shared_mutex mutex_;
		std::map<T1, T2> map_;
	public:
		LockedMap() {}
		virtual ~LockedMap() {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			map_.clear();
		}

		// Careful about issue of race condition
		std::map<T1, T2>& get() {
			return this->map_;
		}

		size_t size() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return map_.size();
		}

		// Manipulation
		void insert(T1&& key, T2&& value) {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			map_[std::move(key)] = std::move(value);
		}

		void insert(const T1& key, const T2& value) {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			map_[key] = value;
		}

		void drop(const T1& key) {
			if (map_.find(key) != map_.end()) {
				map_.erase(key);
			}
		}

		// Access Element

		bool try_find(const T1& key) {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return map_.find(key) != map_.end();
		}

		T2&& fetch(const T1& key) {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			if (map_.empty()) throw "empty";
			if (map_.find(key) == map_.end()) throw "not found";

			T2 value = std::move(map_[key]);
			map_.erase(key);
			return std::move(value);
		}

		T2& peek(const T1& key) {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			if (map_.empty()) throw "empty";
			if (map_.find(key) == map_.end()) throw "not found";

			return map_[key];
		}

		void clear() {
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			map_.clear();
		}

		bool empty() {
			boost::shared_lock<boost::shared_mutex> lock(mutex_);
			return map_.empty();
		}
	};

}