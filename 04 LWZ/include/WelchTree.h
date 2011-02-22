#ifndef JN_WELCHTREE_H
#define JN_WELCHTREE_H

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

	std::pair<size_t, T const *> find(std::string const& key) const {
		size_t current_index = 0;
		Node* current_node = &root_nodes[key[current_index++]];

		for(;current_index < key.length();){
			Node * next_node;
			char const& current_key = key[current_index];
			char const& compare_key = current_node->character;
				 if(current_key < compare_key) next_node = current_node->smaller;
			else if(current_key > compare_key) next_node = current_node->greater;
			else{
				next_node = current_node->longer;
				if(next_node != 0) ++current_index;
			}

			if(next_node == 0) break;
			current_node = next_node;
		}

		return std::make_pair(current_index, &current_node->data);
	}

};

}

#endif // JN_WELCHTREE_H
