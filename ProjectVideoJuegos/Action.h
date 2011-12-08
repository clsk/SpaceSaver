#ifndef _ACTION_H
#define _ACTION_H

#include <map>
#include <string>

struct Action
{
	std::map<std::string,std::string> parameters;
	virtual void act() = 0;
	virtual ~Action() {}
};

struct ExitAction : public Action
{
	void act();
};

struct NextLevelAction : public Action
{
	void act();
};

struct MessageAction : public Action
{
	void act();
};

struct RemoveAction : public Action
{
	void act();
};

struct MoveAction : public Action
{
	void act();
};

struct SleepAction : public Action
{
	void act();
};

#endif // _ACTION_H