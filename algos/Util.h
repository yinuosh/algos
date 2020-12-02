#pragma once

#include "Header.h"

class Util
{
public:
	static void PrintIntArray(int array[], int len, std::string title = "") 
	{
		std::cout << title << ":[";
		if (len > 0 && array) {
			for (int i = 0; i < len; i++) {
				std::cout << array[i];
				if (i != len - 1) {
					std::cout << ",";
				}
			}
		}
		std::cout << "]" << std::endl;
	}

	static void PrintIntArray(int array[], int start, int end, std::string title = "")
	{
		std::cout << title << ":[";
		if (end >= start && array) {
			for (int i = start; i <= end; i++) {
				std::cout << array[i];
				if (i != end) {
					std::cout << ",";
				}
			}
		}
		std::cout << "]" << std::endl;
	}

	static int Rand(int start, int end) {
		if (start == end)return start;
		if (start > end)throw 1;
		return (rand() % (end - start + 1)) + start;
	}

	static void Swap(int data[], int a, int b) {
		int temp = data[a];
		data[a] = data[b];
		data[b] = temp;
	}

	static void CopyIntArr(int source[], int dest[], int len) {
		for (int i = 0; i < len; i++) {
			dest[i] = source[i];
		}
	}
};

