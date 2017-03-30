// UNCOMMENT THE NEXT LINE TO ENABLE THE TESTS AND BEFORE SUBMITTING
// #include "tests.h"
#include <iostream>
#include <string>

template<typename It1, typename It2>
It1 findOccurrence(const It1 from, const It1 to, const It2 begin, const It2 end) {
    const unsigned M = 32768;
    const unsigned C = 1021;
    const unsigned n = std::distance(from, to);
    const unsigned k = std::distance(begin, end);

    unsigned c_to_k = 1;
    unsigned hash_a = 0;
    unsigned hash_b = 0;
    unsigned count = 0;

    // calculate hash for b and first subarray of a
    for (int i = k + count; i-- > count;) {
        hash_a += (*(from + i) * c_to_k) % M;
        hash_b += (*(begin + i) * c_to_k) % M;
        c_to_k = (c_to_k * C) % M;
    }

    if (n >= k) {
        while (count <= n-k) {
            // if hashes are eaual check if strings are equal, else move to next subtring
            if (hash_a == hash_b && std::equal(from + count, from + count + k, begin, end)) {
                return from + count;
			} else {
				hash_a = ((C * hash_a) % M + *(from + count + k) % M - (c_to_k * *(from + count)) % M) % M;  
                ++count;
            }
		}
    } 
	
	return to;
}

int main() {

    std::string input;
    std::getline(std::cin, input);

    std::string substring;
    std::getline(std::cin, substring);

    auto pos = findOccurrence(input.begin(), input.end(), substring.begin(), substring.end());

    if (pos == input.end()) {
        std::cout << "NOT FOUND" << std::endl;
    } else {
        std::cout << std::distance(input.begin(), pos) << std::endl;
    }

    return 0;
}

