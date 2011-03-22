#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>


enum veld_t : char {
	tent = 'T',
	boom = 'B',
	gras = '.',
};

std::ostream& operator<<(std::ostream& os, veld_t const& x){
	return os << (char const&)x;
}

std::istream& operator>>(std::istream& is, veld_t& x){
	veld_t een = (veld_t)is.get();
	switch (een){
		case tent:
		case boom:
		case gras:
			x = een;
			break;
		default:
			is.unget();
			is.setstate(std::ios_base::failbit);
			break;
	}
	return is;
}

struct camping {
	unsigned int width;
	unsigned int height;

	std::vector<std::vector<veld_t>> veld;

	std::vector<unsigned int> horizontal_tent_histogram;
	std::vector<unsigned int> vertical_tent_histogram;

	camping(std::istream& input){
		input >> width >> height;

		for(unsigned int y = 0; y < height; ++y){
			veld.push_back(std::vector<veld_t>(width));
			std::copy(std::istream_iterator<veld_t>(input), std::istream_iterator<veld_t>(), veld.back().begin());

			horizontal_tent_histogram.push_back(*std::istream_iterator<unsigned int>(input));
		}

		std::copy(std::istream_iterator<char>(input), std::istream_iterator<char>(), std::back_inserter(vertical_tent_histogram));
		std::for_each(vertical_tent_histogram.begin(), vertical_tent_histogram.end(), [](unsigned int& x){x=x-'0';});
	}

	friend std::ostream& operator<<(std::ostream& os, camping const & x) {
		std::copy(x.veld.begin(), x.veld.end(), std::istream_iterator<std::vector<veld_t>>(os, "\n"));
	}
};



int main(){
	std::ifstream file("c.txt");
	camping c(file);

	return 0;
}
