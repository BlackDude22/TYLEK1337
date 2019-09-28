#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <bitset>
#include "tylek8137.hpp"
#include "timer.hpp"
#include "picosha2.h"

#include <vector>

std::string getHash(std::string input, std::string algorithm){
	std::string result;
	if (algorithm == "tylek8137"){
		TYLEK8137 h;
		result = h.getHash(input);
	} else if (algorithm == "picosha2")
		result = picosha2::hash256_hex_string(input);
	return result;
}

void hashFile(std::string fileName){
	std::ifstream ifs;
	ifs.open(fileName);
	std::string content = "";
	std::string line;
	while(std::getline(ifs, line))
		content += line;
	std::cout << getHash(content, "tylek8137") << std::endl;
}

void test1(std::string fileName, std::string algorithm){
	std::ifstream ifs;
	ifs.open(fileName);
	std::string line;
	double totalTime = 0;
	while(std::getline(ifs, line)){
		Timer start;
		std::string hashedLine = getHash(line, algorithm);
		totalTime += start.elapsed();
		start.reset();
		std::cout << hashedLine << std::endl;
	}
	std::cout << "Total hashing time: " << totalTime << "s" << std::endl;
}

void test2(int testCount, std::string algorithm){
	std::set<std::string> hashes;
	double totalTime = 0;
	double intervalTime = 0;
	int printInterval = 1e4;
	int duplicate = 0;
	for (int i = 1; i <= testCount; i++){
		Timer start;
		std::string res = getHash(std::to_string(i), algorithm);
		double currentTime = start.elapsed();
		totalTime += currentTime;
		intervalTime += currentTime;
		start.reset();
		auto p = hashes.insert(res);
		if (!p.second)
			duplicate++;
		if (i%((int)printInterval)==0){
			std::cout << "Hashes: " << i << ", Duplicates: " << duplicate << ", Total time: " << totalTime << ", Hashes per second: " << printInterval/intervalTime << ", Average hashes per second: " << i/totalTime << std::endl;
			intervalTime = 0;
		}
	}
}

double compareHashes(std::string hash1, std::string hash2){
	int r = 0;
	for(int i = 0; i < hash1.length(); i++){
		int hval1, hval2;
		std::stringstream ss1, ss2;
		ss1 << hash1.at(i);
  		ss1 >> std::hex >> hval1;
  		ss2 << hash2.at(i);
  		ss2 >> std::hex >> hval2;
  		std::bitset<4> b1(hval1);
  		std::bitset<4> b2(hval2);
  		r += (b1&b2).count();
  		r += ((~b1)&(~b2)).count();
	}
	return r/(4.0*hash1.length());
}

void test3(int testCount, std::string algorithm){
	double min = 1, max = 0;
	double total = 0;
	for (int i = 1; i <= testCount; i++){
		std::string hash1 = getHash(std::to_string(i)+"a", algorithm);
		std::string hash2 = getHash(std::to_string(i)+"A", algorithm);
		double cmp = compareHashes(hash1, hash2);
		if (cmp < min)
			min = cmp;
		if (cmp > max)
			max = cmp;
		total += cmp;
	}
	std::cout << "Similarity ratings: " << std::endl;
	std::cout << "Min: " << min << std::endl;
	std::cout << "Max: " << max << std::endl;
	std::cout << "Avg: " << total/testCount << std::endl;
}

int main(int argc, char *argv[]){
	if (std::string(argv[1]) == "-f")
		hashFile(std::string(argv[2]));
	else if (std::string(argv[1]) == "-t1")
		if (std::string(argv[2]) == "-sha256")
			test1(std::string(argv[3]), "picosha2");
		else
			test1(std::string(argv[2]), "tylek8137");
	else if (std::string(argv[1]) == "-t2")
		if (std::string(argv[2]) == "-sha256")
			test2(atoi(argv[3]), "picosha2");
		else
			test2(atoi(argv[2]), "tylek8137");
	else if (std::string(argv[1]) == "-t3")
		if (std::string(argv[2]) == "-sha256")
			test3(atoi(argv[3]), "picosha2");
		else
			test3(atoi(argv[2]), "tylek8137");
	else 
		std::cout << getHash(std::string(argv[1]), "tylek8137") << std::endl;
}