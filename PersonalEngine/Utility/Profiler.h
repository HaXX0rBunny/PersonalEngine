#pragma once
#include <string>
#include <chrono>
#include <list>
namespace BigginerProfiler
{
	class Block
	{
		std::string name;
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
		std::list<Block*> children;
		Block* parent;
	public:
		Block(const std::string& _name, Block* _parent = nullptr);
		~Block();

		void End();

		double GetSeconds()const;
		std::string GetName()const { return name; };
		Block* GetParent()const { return parent; };

		Block* AddChild(const std::string& _name);
		void Dump(int n = 0)const;
	};
	class Profiler
	{
		static Profiler* ptr;
		Profiler()=default;
		Profiler(const Profiler& other) = delete;
		const Profiler& operator=(const Profiler& other) = delete;
		~Profiler();

		Block* current = nullptr;

		std::list<Block*> fullyFinishedBlocks;
	public:
		void StartBlock(std::string _name);
		void End();
		void Dump();
		void Clear();
		int Getsize();
		const std::list<Block*>& GetBlock();
		static Profiler* GetPtr();
		void DeletePtr();
	};
}
#ifndef  __FUNTION_NAME__
#ifdef WIN32
#define __FUNTION_NAME__ __FUNCTION__
#else
#define __FUNTION_NAME__ __func__
#endif // WIN32
#endif // ! __FUNTION_NAME__



#ifdef _DEBUG
#define DEBUG_PROFILER_START(x) BigginerProfiler::Profiler::GetPtr()->StartBlock(x);
#define DEBUG_PROFILER_END BigginerProfiler::Profiler::GetPtr()->End();
#define DEBUG_PROFILER_DUMP BigginerProfiler::Profiler::GetPtr()->Dump();
#define DEBUG_PROFILER_DELETE BigginerProfiler::Profiler::GetPtr()->DeletePtr();

#else
#define DEBUG_PROFILER_START(x) //
#define DEBUG_PROFILER_END		//
#define DEBUG_PROFILER_DUMP		//
#define DEBUG_PROFILER_DELETE	//
#endif // DEBUG

