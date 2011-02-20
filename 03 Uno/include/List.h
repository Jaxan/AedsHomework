#ifndef JN_LIST_H
#define JN_LIST_H

#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <string>

namespace JN {

template <typename T>

/**
	We hebben de opdracht in c++ gedaan, dus hebben we ons ook aan de c++ conventies gehouden. Alles is engels, en wel zo:
		push_back()		voegAchteraanToe()
		push_front()	voegVooraanToen()
		push()			voegErgensToe()
		pop_front()		pakEerst()
	De iterators zijn standaard c++ iterators, dus je gaat naar het volgende element met de ++ operator, en je krijgt een elemen door te dereferencen (de operator *)

*/
class List {
	struct Node {
		Node(T data) : data(data), next(0) {}
		Node(T data, Node* next) : data(data), next(next) {}

		T data;
		Node* next;
	};

	/**
		We kunnen in iterator geen remove() imeplementeren, omdat deze functie kennis nodig heeft van List (met name de first en last element)
		We vonden de remove() functie sowieso onduidelijk (hoezo kan je alleen iets removen na een next()?)
		Dus zie de erase() functie in List
	*/
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

		iterator operator++(int) {
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
		return (first == 0);
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
		if (empty()) throw std::out_of_range("list::" + (std::string)(__func__) + ": Can't pop this. Thum du du dum. tudu, tudu!");
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

	// we moeten dit in List implementeren, aangezien de eerste of laatste gewijzigd kan worden.
	iterator& erase(iterator& it) {
		if (empty()) throw std::out_of_range("list::" + (std::string)(__func__) + ": Can't erase this. Whoopiedo!");
		if(it.current == first) {
			pop_front();
			it.current = first;
			return it;
		}

		if(it.current == last) {
			last = it.previous;
		}

		it.previous->next = it.current->next;
		delete it.current;
		it.current = it.previous;

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
};

template <typename T>
std::ostream& operator<<(std::ostream& out, List<T>& rh) {
	std::copy(rh.begin(), rh.end(), std::ostream_iterator<T>(out, " "));
	return out;
}
}

#endif // JN_LIST_H
