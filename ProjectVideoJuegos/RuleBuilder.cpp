#include "RuleBuilder.h"

#include <iostream>

#include "ConditionBuilder.h"
#include "ActionBuilder.h"
#include "ticpp.h"

void RuleBuilder::build()
{
	m_rule = new Rule;
	try
	{
		ticpp::Element* element = m_rule_element.Get()->FirstChildElement("Conds");
		ConditionBuilder condition_builder(element);
		condition_builder.build();
		m_rule->conditions = condition_builder.get_conditions();

		element = m_rule_element.Get()->FirstChildElement("Then");
		ActionBuilder action_builder(element);
		action_builder.build();
		m_rule->actions = action_builder.get_actions();
	}
	catch (ticpp::Exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

