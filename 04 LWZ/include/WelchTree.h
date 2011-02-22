#ifndef JN_WELCHTREE_H
#define JN_WELCHTREE_H

#include <vector>

namespace JN {

template <typename T>
class WelchTree {
	struct Node {
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

	WelchTree() {
		for(auto it = 0; it < 256; ++it){
			root_nodes[it].data = root_nodes[it].character = it;
		}
	}

	template <typename IteratorType>
	std::pair<IteratorType, T const *> find(IteratorType begin, IteratorType end) const {
		const Node* current_node = &root_nodes[*begin];

		for(;begin != end;){
			Node * next_node;
			char const& current_key = *begin;
			char const& compare_key = current_node->character;
				 if(current_key < compare_key) next_node = current_node->smaller;
			else if(current_key > compare_key) next_node = current_node->greater;
			else{
				next_node = current_node->longer;
				if(next_node != 0) ++begin;
			}

			if(next_node == 0) break;
			current_node = next_node;
		}

		//Return the iterator to where we read
		return std::make_pair(++begin, &current_node->data);
	}

	template <typename IteratorType, typename OutputIteratorType>
	void compress(IteratorType begin, IteratorType end, OutputIteratorType out){
		while(begin != end){
			auto pair = find(begin, end);
			//Write to compressed stream; increment compressed stream output iterator
			*out++ = pair.second;

			if(pair.first == end){
				//Done!
				insert(begin, end);
				return;
			}

			IteratorType insertion_end = pair.first;
			++insertion_end;

			insert(begin, insertion_end);

			begin = pair.first;
		}

	}

	template <typename IteratorType>
	void insert(IteratorType begin, IteratorType end){

	}

};

}

#endif // JN_WELCHTREE_H
