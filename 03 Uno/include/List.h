#ifndef JN_LIST_H
#define JN_LIST_H

#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <string>

namespace JN {

template <typename T>
class List {
	struct Node {
		Node(T data) : data(data), next(0) {}
		Node(T data, Node* next) : data(data), next(next) {}

		T data;
		Node* next;
	};

	struct iterator : public std::iterator<std::forward_iterator_tag, T> {
		Node* previous;
		Node* current;

		iterator() : previous(0), current(0) {}
		iterator(Node* previous, Node* current) : previous(previous), current(current) {}
		virtual ~iterator() {}

		iterator& operator++() {
			previous = current;
			current = current->next;

			return *this;
		}

		iterator operator++(int foo) {
			iterator temp = *this;

			this->operator++();

			return temp;
		}

		T& operator*() const {
			return current->data;
		}

		T* operator->() const {
			return &current->data;
		}

		void remove() {
			if(previous == 0) {
				throw std::out_of_range("iterator::" + (std::string)(__func__) + ": Can't touch this, THUM-DUDU-DUM, TUDU, TUDU");
			}

			previous->next = current->next;
			delete current;
			current = previous;
		}

		bool operator==(const iterator& rh) {
			return(previous == rh.previous && current == rh.current);
		}

		bool operator!=(const iterator& rh) {
			return !(*this == rh);
		}

	};

public:
	List() :
		first(0),
		last(0) {
	}

	~List() {}

	bool empty() {
		return (first != 0);
	}

	size_t size() {
		size_t length = 0;
		for(auto it = begin(); it != end(); it++) { length++; }
		return length;
	}

	void push_back(T element) {
		if(last == 0) {
			push_front(element);
			return;
		}
		last->next = new Node(element);
		last = last->next;
	}

	void push_front(T element) {
		auto newNode = new Node(element);
		newNode->next = first;
		first = newNode;
		if(last == 0) {
			last = first;
		}
	}

	void push(T element) {
		size_t length = size();
		auto randomIndex = rand() % (length + 1);
		if(randomIndex == length) push_back(element);
		else if(randomIndex == 0) push_front(element);
		else {
			auto newNode = new Node(element);
			auto previous = at(randomIndex-1);
			newNode->next = previous->next;
			previous->next = newNode;
		}
	}

	T pop_front() {
		// Preserve data
		T data = first->data;

		// Replace and delete first
		auto to_be_deleted = first;
		first = first->next;
		delete to_be_deleted;

		return data;
	}

	T operator[](size_t index) {
		return at(index)->data;
	}

	Node* at(size_t index) {
		auto it = first;
		while(index--) {
			if(it->next == 0) {
				throw std::out_of_range("list::" + (std::string)(__func__) + ": Can't touch this, THUM-DUDU-DUM, TUDU, TUDU");
			}

			it = it->next;
		}
		return it;
	}

	iterator begin() {
		return iterator(0, first);
	}

	iterator end() {
		return iterator(last, (last == 0) ? 0 : last->next);
	}

private:
	template <typename U> friend std::ostream& operator<<(std::ostream& out, const List<U>& rh);

	Node* first;
	Node* last;

};

template <typename T>
std::ostream& operator<<(std::ostream& out, List<T>& rh) {
	std::copy(rh.begin(), rh.end(), std::ostream_iterator<T>(out, " "));
	return out;
}
}

#endif // JN_LIST_H
