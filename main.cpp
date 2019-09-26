#include <iostream>
#include "tylek8137.hpp"

int main(int argc, char **argv){
	TYLEK8137 a;
	std::string input = "";
	for (int i = 0; i < argc; ++i)
	  	input += argv[i];
	std::cout << a.getHash(input) << std::endl;
}