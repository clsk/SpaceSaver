#ifndef _CONDITION_H
#define _CONDITION_H

#include <map>
#include <string>

struct Condition
{
	std::map<std::string, std::string> parameters;
	virtual bool evaluate() = 0;
	virtual ~Condition() {}
};

struct ContentCondition : public Condition
{
	bool evaluate();
};

struct CollideCondition : public ContentCondition
{
};


#endif // _CONDITION_H