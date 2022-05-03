# 设计与重构
## 1 需求分析中要考虑的因素
1.可行销性   
2.功能  
3.性能  
4.配套需求  
5.技术（规格）限制  
6.物理形态  
7.节能减排 
8.安全可靠  
9.成本   
10.可安装性   
12.全球化  
13.资料  
14.可采购性  
15.应用环境  
16.市场竞争  
17.商业模式   
# 2 智能指针的析构样例   
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
	system("pause");
	return 0;
}
```
