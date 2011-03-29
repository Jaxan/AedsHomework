
#include <iostream>
#include <fstream>
#include <set>

#include "misc.h"

namespace JN {

template <typename T>
class graph {
public:
	graph() : vertices() {}

private:
	std::map<T, std::set<T>> vertices;

public:
	void add_edge(T const from, T const to){
		auto& self = *this;

		self[from].insert(to);
	}

	auto operator[](T const& key) -> decltype(vertices[key])& {
		return vertices[key];
	}

	auto get_vertices() const -> decltype(vertices) const& {
		return vertices;
	}
};

}

int main() {
	std::ifstream citeeh("picolini.txt");
	citeeh.ignore(); //Ignore the line with the number of citizens.

	JN::graph<int> city_graph;

	int line_number = 1;


	int number_of_civilians;
	while(citeeh >> number_of_civilians){
		for(auto i = 0; i < number_of_civilians; ++i){
			int civilian;
			citeeh >> civilian;
			city_graph.add_edge(line_number, civilian);
		}
		++line_number;
	}

	std::cout << city_graph.get_vertices();

}
