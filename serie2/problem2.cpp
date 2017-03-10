// #include "tests.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

template <typename T>
T find_min (const T begin, const T end) {
	T min = begin;
	for (T it = begin; it != end; ++it) {
		if (*min > *it) {
			min = it;
		}
	}
	return min;
}

template <typename T>
void swap_elements (T elem_1, T elem_2) {
	auto temp = *elem_1;
	*elem_1 = *elem_2;
	*elem_2 = temp;
}


class Selector {
	private:
		std::vector<int> array;
		
		template <typename T>
		T partition (T begin, T end, const int pivot) {
			while (begin < end) {
				while (*begin < pivot) {
					++begin;
				}
				while (*end > pivot) {
					--end;
				}
				swap_elements (begin, end); 
				if (*begin == *end) {
					++begin;
				}
			}
		
			return --begin;		
		}

		template <typename T>
		T rand_pivot(T begin, T end) {
			
			int lower_bound = (end - begin) / 4;
			int upper_bound = (3 * (end - begin)) / 4;
			int pivot = rand() % (end - begin);
						
			while ((lower_bound > pivot) || (upper_bound < pivot)) { 	
				pivot = rand() % (end - begin);
				auto x = array[pivot];

				for (auto it = begin; it != end; ++it) {
					if (*it < x) {
						++pivot;
					}
				}
			}

									
			return begin + pivot;
		}
		
		template <typename T>
		size_t quickselect(T start, T end, size_t k) {
			auto pivot = rand_pivot(start, end);
			auto position = this->partition(start, end, *pivot);
			
			if (k == position - array.begin()) {
			   return k;	
			}

			if (k < position - array.begin()) {
				k = quickselect(start, position, k);
			} else {
				k = quickselect(position, end, k);
			}

			return k;
		}
		

	public:
		Selector (const std::vector<int>& a) : array(a) {};

		int selectRandomized (size_t k) {			
			k = quickselect(array.begin(), --array.end(), k);
			return array[k];
		}
		
		int selectBlum (size_t k);

		int selectBruteForce (size_t k) {
			for (int i = 0; i != array.size(); ++i) {
				swap_elements(find_min(array.begin() + i, array.end()), array.begin() + i);
			}

			return array[k];
		}
		
		void print() {
			for (int i = 0; i != array.size(); ++i) {
				std::cout << array[i] << " ";
			}
			std::cout << "" << std::endl;
		}

};


int main() {
	std::string filename = "test_2.txt";
	std::ifstream in(filename.c_str());

	unsigned int size;
	in >> size;

	std::vector<int> array (size);
	for (int i = 0; i != size; ++i) {
		in >> array[i];
	}
	
	unsigned int k_elem;
	in >> k_elem;

	Selector selector(array);
	
	// randomized algorithm 
	std::cout << selector.selectRandomized(k_elem) << std::endl;

	// brute force algorithm
	std::cout << selector.selectBruteForce(k_elem) << std::endl;

	return 0;
}
