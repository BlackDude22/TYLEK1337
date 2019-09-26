#include <iostream>
#include <set>
#include "hash.hpp"

void test(size_t count){
	std::set<std::string> hashes;
	TYLEK8137 a;
	int maxZeros = 0;
	int duplicate = 0;
	for (int i = 1; i < count; i++){
		std::string res = a.getHash(std::to_string(i));
		auto p = hashes.insert(res);
		if (!p.second){
			duplicate++;
		}
		if (i%((int)1e4)==0)
			std::cout << "hashes: " << i << " duplicates: " << duplicate << " current hash: " << a.getHash(std::to_string(i)) << std::endl;

		for (int j = 0; j < 64; j++){
			if (j > maxZeros){
				maxZeros = j;
				std::cout << "current best: " << j << " zeroes, hash: "<< res << std::endl;
			}
			if (res.at(j) != '0')
				break;
		}
	}
}

int main(int argc, char **argv){
	// test(1e8);

	TYLEK8137 a;
	std::string input = "";
	for (int i = 0; i < argc; ++i)
	  	input += argv[i];
	std::cout << a.getHash(input) << std::endl;
}