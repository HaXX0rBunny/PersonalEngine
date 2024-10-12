#pragma once
#include <string>
class Resource
{
	//pure abtract class
		//IF you inherit from me, you MUST override some fn

protected:
	void* data = nullptr; // why void* (>>pointing anything<<)
	//use static cast for this to become Texture*, Audio* .. when needed

	//fn to return the data

	//pure virtual fn to LOAD data
	//pure virtual fn to Unload data
public:
	virtual void Load(const std::string& filename) = 0;
	virtual void Unload() = 0;
	virtual void* GetData()const = 0;

	virtual ~Resource() = default; //Otherwise you would NOT be deleteing the specialized classes

	const int& GetCounter() const;
	void SetCounter(const int& _counter);
	int counter = 0;
};
