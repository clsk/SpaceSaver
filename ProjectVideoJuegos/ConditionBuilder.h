#ifndef _CONDITION_BUILDER_H
#define _CONDITION_BUILDER_H

#include <list>

#include "ticpp.h"
#include "Condition.h"

class ConditionBuilder
{
public:
	ConditionBuilder(ticpp::Element* condition_elements) : m_condition_elements(condition_elements)
	{}
	std::list<Condition*> get_conditions() { return m_conditions; }

	void build();

private:
	ticpp::Element* m_condition_elements;
	std::list<Condition*> m_conditions;
};

#endif // _CONDITION_BUILDER_H