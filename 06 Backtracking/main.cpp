/*
	Joshua Moerman - 3009408
	Nick Overdijk  - 3029832
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cstdlib>

template <typename T, typename Iterator>
std::vector<std::vector<T>>
search(T goal, Iterator begin, Iterator const& end, std::vector<T>& trace, T const& previous_result = T(1)){
	typedef std::vector<T> trace_t;
	typedef std::vector<trace_t> traces_t;

	//No solution found, return an empty list
	if(begin == end) return traces_t();

	//Create new potential solution
	T const current_result = previous_result**begin;
	trace.push_back(*begin);

	//Was it a solution?
	if(current_result == goal){
		trace_t copy = trace;
		trace.pop_back();
		return traces_t{copy};
	} else {
		++begin;
		traces_t y = search(goal, begin, end, trace, current_result);
		trace.pop_back();
		traces_t x = search(goal, begin, end, trace, previous_result);
		std::copy(x.begin(), x.end(), std::back_inserter(y));
		return y;
	}
}

template <typename T, typename Iterator>
std::vector<std::vector<T>>
search(T goal, Iterator begin, Iterator const& end){
	std::vector<T> ref;
	return search(goal, begin, end, ref);
}

template <typename T>
void AWESOME(){
	//If you guess the random number you get a cookie.
	typename std::vector<T> list{-1, 1, 2, 3, 4, 5, 6, 7, 11, 13, std::rand()};
	//Execellent use of the comma operator to create this AWESOME oneliner.
	auto result = search((std::cout << "Geef een getal op: ", *std::istream_iterator<T>(std::cin)), list.begin(), list.end());
	for(auto it = result.begin(); it != result.end(); ++it){
		//THE 1 AT THE END IS SO THAT YOU GET NICE OUTPUT FOR FREE YES.
		std::copy(it->begin(), it->end(), std::ostream_iterator<T>(std::cout, "*")); std::cout << "1\n";
	}
}

int main(){
	//Om de random seed lastiger te laten voorspellen :)
	std::srand(std::time(0)+*(int*)0x28ff1c);
	while(AWESOME<int>(), true);
    return 0;
}
