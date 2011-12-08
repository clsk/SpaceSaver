#ifndef _RULEBUILDER_H
#define _RULEBUILDER_H

#include "Rule.h"

class RuleBuilder
{
public:
	RuleBuilder(ticpp::Iterator<ticpp::Element>& rule_element) : m_rule_element(rule_element), m_rule(NULL)
	{}

	void build();
	Rule* get_rule() { return m_rule; }

public:
	ticpp::Iterator<ticpp::Element>& m_rule_element;
	Rule* m_rule;
};

#endif // _RULEBUILDER_H