#include <windows.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <string>
#include <mutex>
#include <map>
#include "names.h"
#include <array>
#include <bitset> 
#include<unordered_map>
#include <functional>
#include <sstream>
#include <algorithm>

template<typename T>
class Deleter
{
public:
	void operator()(T* ptr) {
		if (ptr != nullptr) {
			std::cout << "delete all" << std::endl;
			delete[]ptr;
		}
	}


};
int main(int argc, char** argv)
{
	std::unique_ptr<int> test(new int(29));
	std::unique_ptr<int> test2 = std::make_unique<int>(0);
	std::cout << test.get() << std::endl;
	*test = 169;
	std::cout << *(test.get()) << std::endl;
	{
		std::unique_ptr<int, Deleter<int>> ptr(new int[100]);
	}
	{
		std::shared_ptr<int> ptr(new int[100], [](int* ptr) {
			if (ptr != nullptr) {
				std::cout << "delete all" << std::endl;
				delete[]ptr;
			}
			});
	}
	{
		std::unique_ptr<int, std::function<void(int*)>> ptr1(new int[100],
			[](int* p)->void {
				std::cout << "call my lambda deleter:int[]" << std::endl;
				delete[]p;
			}
		);
	}
	system("pause");
	return 0;
}
