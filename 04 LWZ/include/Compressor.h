#ifndef JN_WELCHTREE_H
#define JN_WELCHTREE_H

#include "Party.hardy"

#include <utility>
#include <string>

namespace JN {

// Een algemene welchtree werd het niet, dus hebben we de klasse Compressor genoemd (we maken aannames zoals het altijd inserten van een prefix)
template <typename T>
class Compressor {
public:
	// ctor, vult de root_nodes
	Compressor() : dataCount(256) {
		for(auto it = 0; it < 256; ++it) {
			root_nodes[it].data = root_nodes[it].character = it;
		}
	}

	// wordt niet gebruikt in de compressie, maar zou een mooie functie zijn voor een welch-tree
	template <typename IteratorType>
	std::pair<IteratorType, T const *> find(IteratorType begin, IteratorType end) const {
		auto pair = find_internal(begin, end);
		return std::make_pair(pair.first, &pair.second->data);
	}

	// comprimeert wat tussen begin en end zit, en schrijft naar out.
	// TODO: out is een reference, omdat onze 12bit ostream_iterator niet gekopieerd mag worden :(
	template <typename IteratorType, typename OutputIteratorType>
	void compress(IteratorType begin, IteratorType end, OutputIteratorType& out) {
		while(begin != end) {
			auto pair = find_internal(begin, end);
			//Write to compressed stream; increment compressed stream output iterator
			*out++ = pair.second->data;

			Node* node = const_cast<Node*>(pair.second);
			if(pair.first == end) {
				return;				//Done!
			}

			begin = pair.first;
			insert(begin, node);
		}
	}

private:
	// Node, voor de welch-tree
	struct Node {
		T data;
		char character;				// char moet eigenlijk ge-abstraheerd worden (we gebruiken namelijk ook iterators, waarvan we niet eisen dat ze naar char's wijzen.
		Node* smaller;				// de drie takken (smaller had beter lesser kunnen heten)
		Node* longer;
		Node* greater;

		Node() : data(T()), character(0), smaller(0), longer(0), greater(0) {}
		Node(T data, char c) : data(data), character(c), smaller(0), longer(0), greater(0) {}
	};

	// hiermee wordt de volgende code bepaald
	size_t dataCount;

	// boomtabel, zodat we een instant-lookup hebben bij de eerste stap
	Node root_nodes[256];

	// deze functie vind de grootste prefix, returnt tot waar die heeft kunnen vinden, en de node waar die stopte met zoeken (dit is handig voor de insert, die hier meteen verder kan gaan)
	template <typename IteratorType>
	std::pair<IteratorType, const Node*> find_internal(IteratorType begin, IteratorType end) const {
		const Node* current_node = &root_nodes[(unsigned int)(*begin++)];

		const Node* next_node = current_node->longer;
		while(begin != end && next_node != 0) {
			if(next_node->character == *begin) {
				current_node = next_node;
				next_node = current_node->longer;
				++begin;
			} else if(*begin < next_node->character) {
				next_node = next_node->smaller;
			} else {
				next_node = next_node->greater;
			}
		}

		return std::make_pair(begin, current_node);
	}

	// ipv de iterator konden we ook een char meegeven, maar dit abstraheert van type (en is dus leuker)
	template <typename IteratorType>
	void insert(IteratorType begin, Node* node) {
		auto const& current_key = *begin;
		auto new_node = new Node(dataCount++, current_key);

		if(node->longer == 0) {
			node->longer = new_node;
			return;
		} else {
			node = node->longer;
		}

		while(true) {
			auto const& compare_key = node->character;
			if(current_key < compare_key) {
				if(node->smaller == 0) {
					node->smaller = new_node;
					break;
				} else {
					node = node->smaller;
				}
			} else if(current_key > compare_key) {
				if(node->greater == 0) {
					node->greater = new_node;
					break;
				} else {
					node = node->greater;
				}
			} else {
				throw party(std::string("JN::")+__func__+"Unexpected equality");
			}
		}
	}

};

// comprimeert wat tussen begin en end zit, en schrijft naar out.
template <typename IteratorType, typename OutputIteratorType>
void compress(IteratorType begin, IteratorType end, OutputIteratorType out){
	Compressor<unsigned int> compressor;
	compressor.compress(begin, end, out);
}

}

#endif // JN_WELCHTREE_H
