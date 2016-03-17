//
// Created by Komatta on 2016-03-12.
//

#ifndef ADAPTIVEHUFFMANCODING_NAMEGENERATOR_H
#define ADAPTIVEHUFFMANCODING_NAMEGENERATOR_H
#include <string>
#include <sstream>

class NameGenerator
{
protected:
	std::string mPrefix;
	unsigned long long int mNext;
public:
	NameGenerator(const NameGenerator& rhs)
		: mPrefix(rhs.mPrefix), mNext(rhs.mNext) {}

	NameGenerator(const std::string& prefix) : mPrefix(prefix), mNext(1) {}

	std::string generate()
	{
		std::ostringstream s;
		s << mPrefix << '_' << mNext++;
		return s.str();
	}
	void reset()
	{
		mNext = 1ULL;
	}

	void setNext(unsigned long long int val)
	{
		mNext = val;
	}

	unsigned long long int getNext() const
	{
		return mNext;
	}
};

#endif