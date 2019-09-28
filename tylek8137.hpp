#ifndef TYLEK8137_H
#define TYLEK8137_H

#include <sstream>
#include <cmath>
#include <algorithm>

class TYLEK8137{
	private:
		const static size_t blockLength = 8;
		const static size_t blockCount = 8;
	public:
		TYLEK8137(){
		}

		std::string getHash(std::string input){
			unsigned long long int* hashArray = stringToHash(std::to_string(input.length()));
			generateHash(hashArray, 2);
			for (int i = 0; i < input.length(); i += blockCount){
				std::string substring = input.substr(i, blockCount);
				unsigned long long int* tempArray = stringToHash(substring);
				generateHash(tempArray, 2);
				addHash(hashArray, tempArray);
				generateHash(hashArray, 1);
				free(tempArray);
			}
			generateHash(hashArray, 1);
			std::string result = hexify(hashArray);
			free(hashArray);
			return result;
		}
		
	private:

		unsigned long long int* stringToHash(std::string input){
			unsigned long long int* hashArray = new unsigned long long int[blockCount] ();
			for (int i = 0; i < blockCount && i < input.length(); ++i)
				hashArray[i] = (unsigned long long int)input.at(i);
			return hashArray;
		}

		void generateHash(unsigned long long int* hashArray, int iterations){
			for (int i = 0; i < iterations; i++){
				square(hashArray);
				mix(hashArray);
			}
		}

		void square(unsigned long long int* hashArray){
			for(int i = 0; i < blockCount; i++)
				hashArray[i] = getSquareRootNumbers(hashArray[i]);
		}

		unsigned long long int getSquareRootNumbers(unsigned long long int input){
			double root = sqrt(input);
			double whole, frac;
			frac = std::modf(root, &whole);
			return (((int)whole)%100)*1e6 + (int)(frac*1e6);
		}

		void mix(unsigned long long int* hashArray){
			std::string currentStringArray[blockCount] {};
			for (int i = 0; i < blockCount; i++){
				std::string temp = std::to_string(hashArray[i]);
				temp.resize(blockLength, '0');
				currentStringArray[i] = temp;
			}
			for (int i = 0; i < blockCount; i++){
				std::string temp = "";
				for (int j = 0; j < blockLength; j++){
					temp += currentStringArray[j].at(i);
				}
				hashArray[i] = std::stoi(temp);
			}
		}

		std::string hexify(unsigned long long int* hashArray){
			std::string result = "";
			for(int i = 0; i < blockCount; i++){
				std::string temp;
				unsigned long long int tempint = hashArray[i]/1e8*0xffffffff;
				std::stringstream ss;
				ss << std::hex << tempint;
				ss >> temp;
				if (temp.length() != 8){
					std::reverse(temp.begin(), temp.end());
					temp.resize(8, '0');
					std::reverse(temp.begin(), temp.end());
				}
				result += temp;
			}
			return result;
		}

		void addHash(unsigned long long int* hash1, unsigned long long int* hash2){
			for (int i = 0; i < blockCount; i++){
				hash1[i] = hash1[i]^hash2[i];
				// if (hash1[i]%2 == 0)
				// 	hash1[i] = hash1[i]&hash2[i];
				// else hash1[i] = hash1[i]&hash2[i];
			}
		}
};

#endif