#ifndef JN_WELCHTREE_H
#define JN_WELCHTREE_H

namespace JN {

class WelchTree {
	struct Node {
		int code;
		int character
		Node* smaller;
		Node* longer;
		Node* greater;
	public:
		Node(int code, int c) : code(code), character(c), smaller(0), longer(0), greater(0) {}
	};

    Node root_nodes[256];

public:
};

}

#endif // JN_WELCHTREE_H
