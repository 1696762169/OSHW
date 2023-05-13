#include "../include/SuperBlock.h"

SuperBlock::SuperBlock(const std::shared_ptr<DiskManager>& diskMgr)
{
	m_DiskMgr = diskMgr;
}

std::shared_ptr<SuperBlock> SuperBlock::Init()
{
	/*auto superBlock = std::make_unique<SuperBlock>();
	superBlock->m_FreeCount = SuperBlock::FREE_SECTOR_CAPACITY;
	superBlock->m_InodeCount = SuperBlock::INODE_CAPACITY;
	superBlock->m_Modified = 1;
	superBlock->m_ModifyTime = 0;
	return superBlock;*/
}

std::shared_ptr<SuperBlock> SuperBlock::Load()
{
	return nullptr;
}

void SuperBlock::Update() const
{
	m_DiskMgr->Write(this, sizeof(SuperBlock), DiskManager::SUPER_BLOCK_SECTOR * DiskManager::SECTOR_SIZE);
}

std::shared_ptr<Inode> SuperBlock::AllocInode()
{
	return nullptr;
}
void SuperBlock::FreeInode(int number)
{

}

std::shared_ptr<Buffer> SuperBlock::AllocBuffer()
{
	return nullptr;
}
void SuperBlock::FreeBuffer(int number)
{
	
}
