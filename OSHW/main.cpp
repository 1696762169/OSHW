#include <iostream>
#include "include/DiskManager.h"
#include "include/SuperBlock.h"

fs::path g_ImgPath = "disk.img";

int main()
{
    std::cout << sizeof(std::shared_ptr<DiskManager>);
    // 格式化img文件
    const auto diskManager = std::make_shared<DiskManager>(g_ImgPath);
    diskManager->Init(true);

    const auto c = new char[5];
	diskManager->Read(c, 5, 0);
    for (int i = 0 ; i < 5 ; ++i)
		std::cout << static_cast<int>(c[i]) << ' ';
    delete[] c;

    // 定义全局变量
    const auto sb = SuperBlock::Load();
}