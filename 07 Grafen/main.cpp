// Nick Overdijk	3029832
// Joshua Moerman	3009408

#include <iostream>
#include <fstream>

#include <stdexcept>

#include <list>
#include <set>
#include <map>

// first some generic output functions
template <typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream &os, const std::map<KeyType, ValueType> &x){
	if(x.empty()){
		os << "{ Empty map }";
		return os;
	}

	os << '{';
	for(auto it = x.begin(); it != x.end(); it++){
		os << it->first << " => " << it->second << ", ";
	}
	os << '}';

	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::set<T> &x){
	os << '{';

	auto it = x.begin();
	if(it == x.end()) {
		return os << " empty set }" ;
	}
	os << *it++;
	for(; it != x.end(); it++){
		os << " " << *it;
	}
	os << '}';

	return os;
}

namespace JN {
// now the fun starts :D
// The minimalistic graph class
template <typename T>
class graph {
private:
	std::map<T, std::set<T>> vertices;

public:
	graph() : vertices() {}

	// adds edge to graph (long live c++-map ;) )
	void add_edge(T const from, T const to){
		vertices[from].insert(to);
		vertices[to];
	}

	// returns topcat
	T mightiest(){
		auto mightiest_so_far = vertices.begin()->first;
		auto max_size = connected(mightiest_so_far).size();
		auto it = vertices.begin();

		while(++it != vertices.end()){
			auto const connected_leute = connected(it->first);
			if(connected_leute.size() > max_size){
				mightiest_so_far = it->first;
				max_size = connected_leute.size();
			}
		}

		return mightiest_so_far;
	}

	// returns component which is "in greep" of koning
	std::set<T> connected(T const koning) const {
		std::set<T> connected_to;
		std::list<T> to_visit{koning};

		std::map<T, bool> visited;

		while(!to_visit.empty()){
			auto visit_me = to_visit.front();
			to_visit.pop_front();

			if(visited[visit_me] == true) continue;

			auto connected_nodes_iterator = vertices.find(visit_me);
			if(connected_nodes_iterator == vertices.end()) throw std::runtime_error("Dat is geen bewoner vriend");

			auto connected_nodes = connected_nodes_iterator->second;
			visited[visit_me] = true;

			std::copy(connected_nodes.begin(), connected_nodes.end(), std::inserter(connected_to, connected_to.begin()));
			std::copy(connected_nodes.begin(), connected_nodes.end(), std::back_inserter(to_visit));
		}

		//std::cout << "For koning " << koning << " set " << connected_to << std::endl;
		return connected_to;
	}

	// nice getter
	auto get_vertices() const -> decltype(vertices) const& {
		return vertices;
	}
};

}

int main() {
	// read file (and ignore first number, since its useless....)
	std::ifstream citeeh("picolini.txt");
	{ int bin; citeeh >> bin; }

	JN::graph<int> city_graph;

	// adding stuff to graph
	int line_number = 0;
	int number_of_civilians;
	while(citeeh >> number_of_civilians){
		for(auto i = 0; i < number_of_civilians; ++i){
			int civilian;
			citeeh >> civilian;
			city_graph.add_edge(line_number, civilian);
		}
		++line_number;
	}

	// outputing analyses
	std::cout << "City-connection-analyzer-2000-beta found the following connections within the given city" << std::endl;
	std::cout << city_graph.get_vertices() << std::endl;

	std::cout << "Machtigste: " << city_graph.mightiest() << std::endl;

	// nice interactive shell to ask componenets
	std::cout << "\nEntering interactive shell for component-finder-2000-beta, please stand by..." << std::endl;
	int next_civilian = 0;
	while(std::cout << "Geef een nummer van een bewoner op: ", std::cin >> next_civilian){
		try {
			std::cout << city_graph.connected(next_civilian) << std::endl;
		} catch (std::exception const& e){
			std::cerr << e.what() << std::endl;
		}
	}

	return 0;
}
