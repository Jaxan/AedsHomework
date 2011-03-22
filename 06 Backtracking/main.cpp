#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cstdlib>

template <typename T, typename Iterator>
std::vector<std::vector<T>>
search(T goal, Iterator begin, Iterator const& end, std::vector<T> const& trace = std::vector<T>(), T const& previous_result = T(1)){
	typedef std::vector<T> trace_t;
	typedef std::vector<trace_t> traces_t;
	if(begin == end) return traces_t();
	T const current_result = previous_result**begin;
	trace_t new_trace[2] = {trace, trace};
	new_trace[1].push_back(*begin);
	if(current_result == goal){
		return traces_t{new_trace[1]};
	} else {
		++begin;
		traces_t x = search(goal, begin, end, new_trace[0], previous_result);
		traces_t y = search(goal, begin, end, new_trace[1], current_result);
		std::copy(x.begin(), x.end(), std::back_inserter(y));
		return y;
	}
}

template <typename T>
void AWESOME(){
	typename std::vector<T> list{-1, 1, 2, 3, 4, 5, 6, 7, 11, 13, std::rand()};
	auto result = search((std::cout << "Geef een getal op: ", *std::istream_iterator<T>(std::cin)), list.begin(), list.end());
	for(auto it = result.begin(); it != result.end(); ++it){
		std::copy(it->begin(), it->end(), std::ostream_iterator<T>(std::cout, "*")); std::cout << "1\n";
	}
}

int main(){
	//Om de random seed lastiger te laten voorspellen :)
	std::srand(std::time(0)+*(int*)0x28ff1c);
	while(AWESOME<int>(), true);
    return 0;
}
