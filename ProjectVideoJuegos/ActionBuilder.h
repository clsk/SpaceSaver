#ifndef _ACTION_BUILDER_H
#define _ACTION_BUILDER_H

#include <list>
#include "Rule.h"
#include "Action.h"

class ActionBuilder
{
public:
	ActionBuilder(ticpp::Element* action_elements) : m_action_elements(action_elements)
	{}
	void build();
	std::list<Action*> get_actions() { return m_actions; }

private:
	ticpp::Element*		m_action_elements;
	std::list<Action*>	m_actions;
};

#endif // _CONDITION_BUILDER_H