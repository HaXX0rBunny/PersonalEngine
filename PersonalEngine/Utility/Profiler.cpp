#include "Profiler.h"
#include <iostream>
#include <iomanip>
BigginerProfiler::Block::Block(const std::string& _name, Block* _parent) : name(_name), parent(_parent)
{
	start = std::chrono::steady_clock::now();
}

BigginerProfiler::Block::~Block()
{
	for (auto it : children)
		delete it;
	children.clear();
}

void BigginerProfiler::Block::End()
{
	end = std::chrono::steady_clock::now();
}



double BigginerProfiler::Block::GetSeconds() const
{
	return std::chrono::duration<double>(end - start).count();
}


BigginerProfiler::Block* BigginerProfiler::Block::AddChild(const std::string& _name)
{
	Block* nBlock = new Block(_name, this);
	children.push_back(nBlock);

	return nBlock;
}
void BigginerProfiler::Block::Dump(int n)const
{
	//print correct ammount of tabs
	for (int i = 0; i < n; ++i)
		std::cout << "\t";
	//print name and second
	std::cout << GetName() << " in " << std::fixed << std::setprecision(7) << GetSeconds() << " seconds" << std::endl;

	//print children
	for (const auto* c : children)
		c->Dump(n + 1);

}
BigginerProfiler::Profiler* BigginerProfiler::Profiler::ptr = nullptr;
BigginerProfiler::Profiler::~Profiler()
{
	Clear();
}
void BigginerProfiler::Profiler::StartBlock(std::string _name)
{
	if (!current)
	{
		current = new Block(_name); //I am root
	}
	else
		current = current->AddChild(_name);
}

void BigginerProfiler::Profiler::End()
{
	if (current)
	{
		//stop counting time on current block
		current->End();
		//go 1 stemp back
		Block* parent = current->GetParent();

		//if no parent. Push current to fullyFinished
		if (!parent)
			fullyFinishedBlocks.push_back(current);
		current = parent;
	}
}

void BigginerProfiler::Profiler::Dump()
{
	std::cout << fullyFinishedBlocks.size() << std::endl;
	for (const auto* b: fullyFinishedBlocks)
	{
		b->Dump();
	}
}

void BigginerProfiler::Profiler::Clear()
{
	//iterate end UNTIL current in nullptr
	while (current)
		End();
	//delete all the finished nodes
	for (auto it : fullyFinishedBlocks)
		delete it;
	fullyFinishedBlocks.clear();
}

int BigginerProfiler::Profiler::Getsize()
{
	return fullyFinishedBlocks.size();
}

const std::list<BigginerProfiler::Block*>& BigginerProfiler::Profiler::GetBlock()
{
	return fullyFinishedBlocks;
}

BigginerProfiler::Profiler* BigginerProfiler::Profiler::GetPtr()
{
	if (!ptr)
		ptr = new Profiler;
	return ptr;
}

void BigginerProfiler::Profiler::DeletePtr()
{
	if (ptr)
		delete ptr;
	ptr = nullptr;
}
