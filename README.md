***
# 智能指针的析构样例   
>shared_ptr 在默认情况下是不能指向数组的,原因是 shared_ptr 默认的删除器是使用 Delete 对智能指针中的对象进行删除，而 delete 要求 new 时是单一指针 Delete时也应该是指针 new时是数组 delete 也应该用数组类型去delete.
``` c++
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
//但是每个智能指针都写一个类是不是好烦？  
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
	// 此处需要注意shared_ptr 和unique_ptr在定义析构器时略有不同
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
	//相比与shared_ptr unique_ptr对于动态数组的管理就轻松多了 我们只需要直接使用即可
        //unique_ptr<int[]>unique(new int[100]);
	system("pause");
	return 0;
}
```
