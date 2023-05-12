#pragma once
#include <memory>
#include "Buffer.h"
#include "DiskManager.h"

/**
 * \brief 超级块 定义文件系统的全局变量
 */
class SuperBlock
{
public:
	static constexpr int FREE_SECTOR_CAPACITY = 120;	// 直接管理的空闲盘块最大数量
	static constexpr int INODE_CAPACITY = 120;	// 直接管理的空闲外存Inode最大数量
	static constexpr int PADDING_SIZE = 2 * DiskManager::SECTOR_SIZE / 4 - FREE_SECTOR_CAPACITY - INODE_CAPACITY - 2 - 2;	// 填充区大小

public:
	static std::unique_ptr<SuperBlock> Init();	// 初始化超级块
	static std::unique_ptr<SuperBlock> Load();	// 从磁盘加载超级块
	void Update();	// 更新超级块到磁盘

	std::shared_ptr<Inode> AllocInode();	// 分配一个Inode
	void FreeInode(int number);	// 释放一个Inode

	std::shared_ptr<Buffer> AllocBuffer();	// 分配一个缓冲区
	void FreeBuffer(int number);	// 释放一个缓冲区

private:
	int freeCount;	// 直接管理的空闲盘块数
	int freeSectors[FREE_SECTOR_CAPACITY];	// 直接管理的空闲盘块索引表

	int inodeCount;	// 直接管理的空闲外存Inode数
	int inodes[INODE_CAPACITY];	// 直接管理的空闲外存Inode索引表

	int modified;	// 被更改标识
	int modifyTime;	// 最近一次更新时间

	int padding[PADDING_SIZE];	// 填充区
};