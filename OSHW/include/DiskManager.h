#pragma once
#include "Inode.h"
#include <filesystem>
#include <Windows.h>
namespace fs = std::filesystem;

/**
 * \brief img文件操作类
 */
class DiskManager
{
public:
	static constexpr int SECTOR_SIZE = 512;	// 扇区大小

	static constexpr int SUPER_BLOCK_SECTOR = 0;	// 定义SuperBlock位于磁盘上的扇区号 占据0、1两个扇区

	static constexpr int DATA_START_SECTOR = 1024;		// 数据区的起始扇区号
	static constexpr int DATA_SIZE = 1 << 14;	// 数据区占据的扇区数量（16384）
	static constexpr int DATA_END_SECTOR = DATA_SIZE + DATA_START_SECTOR - 1;	// 数据区的结束扇区号

	static constexpr int ROOT_INODE_NO = 1;	// 文件系统根目录外存Inode编号
	static constexpr int INODE_PER_SECTOR = SECTOR_SIZE / sizeof(DiskInode);	// 每个磁盘块可以存放的外存Inode数
	static constexpr int INODE_START_SECTOR = SUPER_BLOCK_SECTOR + 2;	// 外存Inode区位于磁盘上的起始扇区号
	static constexpr int INODE_SIZE = DATA_START_SECTOR - INODE_START_SECTOR;	// 外存Inode区占用的盘块数
public:
	explicit DiskManager(const std::filesystem::path& imgPath);
	~DiskManager();

	void Init(const bool forceCreate);	// 初始化DiskManager状态 完成文件映射
	void Read(char* content, int size, int offset) const;	// 从img文件读取内容到内存（需要保证content指向的空间足够大）
	void Write(const void* content, int size, int offset) const;	// 将内存中的内容写入img文件

private:
	static void CreateDisk();	// 格式化img文件

private:
	const std::filesystem::path m_ImgPath;	// img文件路径
	bool m_NeedFormatting;	// 是否需要格式化img文件

	HANDLE m_FileHandle;	// img文件句柄
	HANDLE m_MappingHandle;	// img文件映射句柄

	char* m_Ptr;	// img文件映射指针
};