#include "Rule.h"

#include "stdafx.h"

Rule::Rule()
{
}

Rule::~Rule()
{
	for (std::list<Condition*>::iterator Iter = conditions.begin(); Iter != conditions.end(); ++Iter)
		delete *Iter;

	for (std::list<Action*>::iterator Iter = actions.begin(); Iter != actions.end(); ++Iter)
		delete *Iter;
}