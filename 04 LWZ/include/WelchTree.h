#ifndef JN_WELCHTREE_H
#define JN_WELCHTREE_H

#include "Party.hardy"

#include <vector>
#include <tuple>
#include <exception>

namespace JN {

template <typename T>
class WelchTree {
	struct Node {
		// TODO: for supergeneric-code: make char a template argument (atomic type or something), see also iterators
		T data;
		char character;
		Node* smaller;
		Node* longer;
		Node* greater;
		Node() : data(T()), character(0), smaller(0), longer(0), greater(0) {}

		Node(T data, char c) : data(data), character(c), smaller(0), longer(0), greater(0) {}

		Node* where_to(const char compare){
			if(compare < character) return smaller;
			if(compare > character) return greater;
			return longer;
		}

	};

	Node root_nodes[256];

public:

	WelchTree() : dataCount(256) {
		for(auto it = 0; it < 256; ++it){
			root_nodes[it].data = root_nodes[it].character = it;
		}
	}

	template <typename IteratorType>
	std::pair<IteratorType, T const *> find(IteratorType begin, IteratorType end) const {
		auto pair = find_internal(begin, end);
		return std::make_pair(pair.first, &pair.second->data);
	}

	template <typename IteratorType, typename OutputIteratorType>
	void compress(IteratorType begin, IteratorType end, OutputIteratorType out){
		while(begin != end){
			auto pair = find_internal(begin, end);
			//Write to compressed stream; increment compressed stream output iterator
			*out++ = pair.second->data;

			Node * node = const_cast<Node*>(pair.second);
			if(pair.first == end){
				//Done!
				return;
			}

			begin = pair.first;
			insert(begin, node);
		}
	}

private:
	size_t dataCount;

	template <typename IteratorType>
	std::pair<IteratorType, const Node*> find_internal(IteratorType begin, IteratorType end) const {
		const Node* current_node = &root_nodes[*begin++];

		const Node* next_node = current_node->longer;
		while (begin != end && next_node != 0){
			if (next_node->character == *begin) {
				current_node = next_node;
				next_node = current_node->longer;
				++begin;
			} else if (*begin < next_node->character) {
				next_node = next_node->smaller;
			} else {
				next_node = next_node->greater;
			}
		}

		return std::make_pair(begin, current_node);
	}

	template <typename IteratorType>
	void insert(IteratorType begin, Node* node){
		auto const& current_key = *begin;
		auto new_node = new Node(dataCount++, current_key);

		if (node->longer == 0){
			node->longer = new_node;
			return;
		} else {
			node = node->longer;
		}

		while(true){
			auto const& compare_key = node->character;
			if(current_key < compare_key){
				if(node->smaller == 0){
					node->smaller = new_node;
					break;
				} else {
					node = node->smaller;
				}
			} else if(current_key > compare_key){
				if(node->greater == 0){
					node->greater = new_node;
					break;
				} else {
					node = node->greater;
				}
			} else {
				throw party();
			}
		}
	}

};

}

#endif // JN_WELCHTREE_H
