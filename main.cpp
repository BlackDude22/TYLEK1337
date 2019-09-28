#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <bitset>
#include "tylek8137.hpp"
#include "timer.hpp"

void hashFile(std::string fileName){
	std::ifstream ifs;
	TYLEK8137 hash;
	ifs.open(fileName);
	std::string content = "";
	std::string line;
	while(std::getline(ifs, line))
		content += line;
	std::cout << hash.getHash(content) << std::endl;
}

void test1(std::string fileName){
	std::ifstream ifs;
	TYLEK8137 hash;
	ifs.open(fileName);
	std::string line;
	double totalTime = 0;
	while(std::getline(ifs, line)){
		Timer start;
		std::string hashedLine = hash.getHash(line);
		totalTime += start.elapsed();
		start.reset();
		std::cout << hashedLine << std::endl;
	}
	std::cout << "Total hashing time: " << totalTime << "s" << std::endl;
}

void test2(int testCount){
	std::set<std::string> hashes;
	TYLEK8137 hash;
	double totalTime = 0;
	double intervalTime = 0;
	int printInterval = 1e4;
	int duplicate = 0;
	for (int i = 1; i <= testCount; i++){
		Timer start;
		std::string res = hash.getHash(std::to_string(i));
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

void test3(int testCount){
	TYLEK8137 hash;
	double min = 1, max = 0;
	double total = 0;
	for (int i = 1; i <= testCount; i++){
		std::string hash1 = hash.getHash(std::to_string(i)+"a");
		std::string hash2 = hash.getHash(std::to_string(i)+"A");
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
	TYLEK8137 hash;
	if (std::string(argv[1]) == "-f")
		hashFile(std::string(argv[2]));
	else if (std::string(argv[1]) == "-t1")
		test1(std::string(argv[2]));
	else if (std::string(argv[1]) == "-t2")
		test2(atoi(argv[2]));
	else if (std::string(argv[1]) == "-t3")
		test3(atoi(argv[2]));
	else 
		std::cout << hash.getHash(std::string(argv[1])) << std::endl;
}
