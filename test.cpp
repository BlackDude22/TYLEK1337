#include <iostream>
#include <set>
#include "tylek8137.hpp"

void test(size_t count){
	std::set<std::string> hashes;
	TYLEK8137 a;
	int duplicate = 0;
	for (int i = 1; i < count; i++){
		std::string res = a.getHash(std::to_string(i));
		auto p = hashes.insert(res);
		if (!p.second)
			duplicate++;
		if (i%((int)1e4)==0)
			std::cout << "hashes: " << i << " duplicates: " << duplicate << " current hash: " << a.getHash(std::to_string(i)) << std::endl;
	}
}

int main(int argc, char **argv){
	test(1e8);
}