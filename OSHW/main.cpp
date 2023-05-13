#include <iostream>
#include "include/DiskManager.h"

fs::path g_ImgPath = "disk.img";

int main()
{
    // 定义全局变量
    const auto diskManager = std::make_unique<DiskManager>(g_ImgPath);

    // 格式化img文件
    diskManager->Init(true);

    const auto c = new char[5];
	diskManager->Read(c, 5, 0);
    for (int i = 0 ; i < 5 ; ++i)
		std::cout << static_cast<int>(c[i]) << ' ';
    delete[] c;
}