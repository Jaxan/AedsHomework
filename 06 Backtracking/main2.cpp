/*
	Joshua Moerman - 3009408
	Nick Overdijk  - 3029832
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>


//generic vector stream insertion operator! woeii.
template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &x){
	os << '{';

	typename std::vector<T>::const_iterator it = x.begin();
	os << *it++;
	for(; it != x.end(); it++){
		os << " " << *it;
	}
	os << '}';

	return os;
}

// the possible tiles
enum veld_t : char {
	tent = 'T',
	boom = 'B',
	gras = '.',
};

// I/O of veld_t
std::ostream& operator<<(std::ostream& os, veld_t const& x){
	return os << (char const&)x;
}
std::istream& operator>>(std::istream& is, veld_t& x){
	char c;
    is >> c;
    c = std::toupper(c);

	switch ((veld_t)c){
		case tent:
		case boom:
		case gras:
			x = (veld_t)c;
			break;
		default:
			is.setstate(std::ios_base::failbit);
			break;
	}
	return is;
}

struct camping {
	std::vector<std::vector<veld_t>> veld;

	std::vector<unsigned int> horizontal_tent_histogram;
	std::vector<unsigned int> vertical_tent_histogram;

	std::vector<unsigned int> horizontal_tent_current_histogram;
	std::vector<unsigned int> vertical_tent_current_histogram;

	unsigned int max_tents;
	unsigned int tents;

	// ctor
	camping(std::istream& input) : veld(), horizontal_tent_current_histogram(), vertical_tent_current_histogram(), max_tents(0), tents(0) {
		unsigned int width, height;
		input >> height >> width;
		horizontal_tent_current_histogram.resize(height);
		vertical_tent_current_histogram.resize(width);

		//"Recht zo die gaat", copy copy copy
		for(unsigned int y = 0; y < height; ++y){
			veld.push_back(std::vector<veld_t>(width));
			std::for_each(veld.back().begin(), veld.back().end(), [&](veld_t& x) {input >> x;});
			horizontal_tent_histogram.push_back(*std::istream_iterator<unsigned int>(input));
		}
		std::copy(std::istream_iterator<char>(input), std::istream_iterator<char>(), std::back_inserter(vertical_tent_histogram));
		std::for_each(vertical_tent_histogram.begin(), vertical_tent_histogram.end(), [](unsigned int& x){x=x-'0';});

		max_tents = std::accumulate(horizontal_tent_histogram.begin(), horizontal_tent_histogram.end(), 0);
	}

	// don't go further if we have more tents to place than there are places left on the camping
	bool should_continue(unsigned int row, unsigned int column) const {
		unsigned int max_column = veld.front().size()-1;
		unsigned int max_row = veld.size()-1;

		unsigned int achievable = (max_row - row) * (max_column+1) + (max_column - column + 1);

		return (achievable >= (max_tents - tents));
	}

	// the checks are pretty easy
	bool can_place_tent(unsigned int row, unsigned int column) const {
		if ( veld[row][column] != gras ) return false;
		if ( tents == max_tents ) return false;
		if ( horizontal_tent_current_histogram[row] == horizontal_tent_histogram[row] ) return false;
		if ( vertical_tent_current_histogram[column] == vertical_tent_histogram[column] ) return false;

		//Figure out the start and end column and row so that we don't need to do a lot of cascaded ifs
		unsigned int max_column = veld.front().size()-1;
		unsigned int max_row = veld.size()-1;

		unsigned int start_row = std::max((int)row-1, 0);
		unsigned int start_column = std::max((int)column-1, 0);
		unsigned int end_row = std::min(row+1, max_row);
		unsigned int end_column = std::min(column+1, max_column);

		for(auto x = start_row; x <= end_row; ++x){
			for(auto y = start_column; y <= end_column; ++y){
				//If we find a tent in this spot, return false
				if(veld[x][y] == tent) return false;
			}
		}

		//If there's no tent here, we haven't passed the max tents, in row as well in column, there's no tent next to us,
		// ... and we are next to a tree: return true
		if(veld[start_row][column] == boom) return true;
		if(veld[end_row][column] == boom) return true;
		if(veld[row][start_column] == boom) return true;
		if(veld[row][end_column] == boom) return true;

		//Apparently we weren't next to a tree. :(
		return false;
	}

	void place_tent(unsigned int row, unsigned int column) {
		veld[row][column] = tent;
		++tents;
		++horizontal_tent_current_histogram[row];
		++vertical_tent_current_histogram[column];
	}

	void remove_tent(unsigned int row, unsigned int column) {
		veld[row][column] = gras;
		--tents;
		--horizontal_tent_current_histogram[row];
		--vertical_tent_current_histogram[column];
	}

	bool solved(){
		return tents == max_tents;
	}

	// output, not as nice as the original, but very short and easy to expand.
	friend std::ostream& operator<<(std::ostream& os, camping const & x) {
		std::copy(x.veld.begin(), x.veld.end(), std::ostream_iterator<std::vector<veld_t>>(os, "\n"));
		os << x.horizontal_tent_histogram << '\n';
		os << x.vertical_tent_histogram << '\n';
		os << "Tents " << x.tents << '/' << x.max_tents << '\n';

		return os;
	}
};

std::vector<camping> solve(camping& previous_result, unsigned int current_row = 0, unsigned int current_column = 0){
	// go to the first place where we have a choice (so if we cannot put a tent here, move on)
	while(!previous_result.can_place_tent(current_row, current_column)){
		// don't go any further if we know we cant find a solution anymore
		if(!previous_result.should_continue(current_row, current_column)) return std::vector<camping>{};
		++current_column;
		if(current_column == previous_result.veld.front().size()){
			current_column = 0;
			++current_row;
			if(current_row == previous_result.veld.size()) {
				return std::vector<camping>{};
			}
		}
	}

	// don't copy the camping, a reference is fine
	camping& new_result = previous_result;
	unsigned int tent_place_row = current_row;
	unsigned int tent_place_column = current_column;
	new_result.place_tent(current_row, current_column);

	if(new_result.solved()){
		// WE FOUND A SOLUTION, it is nice to output right away!
		std::cout << new_result << std::endl;
		std::vector<camping> return_value{new_result};
		new_result.remove_tent(tent_place_row, tent_place_column);
		return return_value;
	}

	// step one further
	++current_column;
	if(current_column == previous_result.veld.front().size()){
		current_column = 0;
		++current_row;
		if(current_row == previous_result.veld.size()) {
			return std::vector<camping>{};
		}
	}

	auto y = solve(new_result, current_row, current_column);
	// restore the camping without thee change
	previous_result.remove_tent(tent_place_row, tent_place_column);
	auto x = solve(previous_result, current_row, current_column);

	// merge solutions
	std::copy(x.begin(), x.end(), std::back_inserter(y));

	return x;
}


int main(){
	std::ifstream file("c7.txt");
	camping c(file);

	// output the problem to solve
	std::cout << c;

	// we are outputting to solutions as we find them (we are also storing them in a list, but we are not really interested in that)
	solve(c);

	return 0;
}


/*
	our solution:

	{T . B . B . . T B .}
	{B . T . T . . . . .}
	{T . . B . . . . B T}
	{B . . T . B T . . .}
	{. T . B . . . . T B}
	{. B . T . . T B . .}
	{. T . B . B . . T B}
	{. B . T . T . . . .}
	{. . . . . . B T . .}
	{T B T B . . . . B T}
	{2 2 2 2 2 2 2 2 1 3}	(nb this array should be placed next to the matrix)
	{3 2 2 3 1 1 2 2 2 2}
	Tents 20/20

*/
