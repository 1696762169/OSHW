#include <iostream>
#include <fstream>
#include "../include/DiskManager.h"
#include "../include/SuperBlock.h"

DiskManager::DiskManager(const std::filesystem::path& imgPath) : m_ImgPath(imgPath)
{
	// 创建文件
	if (!exists(imgPath))
	{
		std::ofstream ofs(imgPath, std::ios::trunc);
		const char* padding = new char[(DATA_END_SECTOR + 1) * SECTOR_SIZE];
		ofs.write(padding, (DATA_END_SECTOR + 1) * SECTOR_SIZE);
		ofs.close();
		delete[] padding;
		m_NeedFormatting = true;
	}
	
	// 文件句柄
	m_FileHandle = CreateFile(imgPath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (m_FileHandle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "无法打开img文件: " << imgPath << std::endl;
		throw std::runtime_error("无法打开img文件:");
	}

	// 创建文件映射对象
	m_MappingHandle = CreateFileMapping(m_FileHandle, nullptr, PAGE_READWRITE, 0, 0, nullptr);
	if (m_MappingHandle == nullptr)
	{
		std::cerr << "无法创建img文件映射对象" << std::endl;
		CloseHandle(m_FileHandle);
		throw std::runtime_error("无法创建img文件映射对象");
	}

	// 将文件映射到内存
	m_Ptr = static_cast<char*>(MapViewOfFile(m_MappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, GetFileSize(m_FileHandle, nullptr)));
	if (m_Ptr == nullptr)
	{
		std::cerr << "无法将img文件映射到内存" << std::endl;
		CloseHandle(m_MappingHandle);
		CloseHandle(m_FileHandle);
		throw std::runtime_error("无法将img文件映射到内存");
	}
}
DiskManager::~DiskManager()
{
	// 关闭文件映射
	UnmapViewOfFile(m_Ptr);
	// 关闭文件映射对象
	CloseHandle(m_MappingHandle);
	// 关闭文件句柄
	CloseHandle(m_FileHandle);
}

void DiskManager::Init(const bool forceCreate = false)
{
	if (m_NeedFormatting || forceCreate)
	{
		CreateDisk();
		m_NeedFormatting = false;
	}
}

void DiskManager::Read(char* content, const int size, const int offset) const
{
	CopyMemory(content, m_Ptr + offset, size);
}

void DiskManager::Write(const void * const content, const int size, const int offset) const
{
	CopyMemory(m_Ptr + offset, content, size);
}

void DiskManager::CreateDisk()
{
	// 初始化超级块
	auto sb = std::make_unique<SuperBlock>();
	sb->Init();
	Write(sb.get(), sizeof(SuperBlock), SUPER_BLOCK_SECTOR * SECTOR_SIZE);
}
