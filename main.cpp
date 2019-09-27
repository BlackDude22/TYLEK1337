#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "tylek8137.hpp"

int main(int argc, char *argv[]){
	TYLEK8137 a;
	bool fos = (std::string(argv[1]) == "-f" ? true : false);
	if (fos){
		std::ifstream ifs;
		ifs.open(argv[2]);
		bool lnl = (std::string(argv[3]) == "1" ? true : false);
		std::string x = "";
		if (lnl){
			while(std::getline(ifs, x))
				std::cout << a.getHash(x) << std::endl;
		} else {
			std::string temp;
			while(std::getline(ifs, temp))
				x += temp;
			std::cout << x << " " << a.getHash(x) << std::endl;
		}
	} else {
		std::cout << a.getHash(argv[1]) << std::endl;
	}
}