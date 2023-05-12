#pragma once
/**
 * \brief 内存Inode类
 */
class Inode
{
};

/**
 * \brief 外存Inode类
 * 为了保持外存Inode的大小，此处直接照抄Unix
 */
class DiskInode
{
public:
	int		mode;			// 状态的标志位，定义见enum INodeFlag
	int		linkCount;		// 文件联结计数，即该文件在目录树中不同路径名的数量

	short	uid;			// 文件所有者的用户标识数
	short	gid;			// 文件所有者的组标识数

	int		size;			// 文件大小，字节为单位
	int		address[10];		// 用于文件逻辑块好和物理块好转换的基本索引表

	int		accessTime;		// 最后访问时间
	int		modifyTime;		// 最后修改时间
};
