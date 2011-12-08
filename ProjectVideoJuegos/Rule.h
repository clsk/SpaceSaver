#ifndef _RULE_H
#define _RULE_H

#include <list>
#include <string>
#include <utility>

#include "ticpp.h"
#include "Condition.h"
#include "Action.h" 

typedef std::pair<std::string,std::string> Parameter;

class RuleBuilder;
class Rule
{
public:
	Rule();
	~Rule();

	void execute()
	{
		for (std::list<Condition*>::iterator Iter = conditions.begin(); Iter != conditions.end(); ++Iter)
			if ((*Iter)->evaluate() == false)
				return;

		for (std::list<Action*>::iterator Iter = actions.begin(); Iter != actions.end(); ++Iter)
			(*Iter)->act();
	}
private:
	friend class RuleBuilder;
	std::list<Condition*> conditions;
	std::list<Action*> actions;
};

#endif // _RULE_H