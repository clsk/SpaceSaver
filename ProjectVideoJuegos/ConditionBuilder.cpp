#include "ConditionBuilder.h"

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <cassert>

#include "Condition.h"
#include "ticpp.h"

using std::string;
using std::cout;
using std::endl;

#define CONDITION_CONTENT "Content"
#define CONDITION_COLLIDE "Collide"

void ConditionBuilder::build()
{
	ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(m_condition_elements); child != child.end(); child++)
	{
		string type;
		child->GetValue(&type);
		Condition* condition = NULL;
		if (type == "Content")
			condition = new ContentCondition;
		else if (type == "Collide")
			condition = new CollideCondition;

		assert(condition != NULL);

		// Get parameters (XML Attributes)
		ticpp::Iterator< ticpp::Attribute > attribute;        
		for(attribute = attribute.begin(child.Get()); attribute != attribute.end(); attribute++)       
		{
			string name;
			string value;
			attribute->GetName(&name);            
			attribute->GetValue(&value);
			condition->parameters.insert(std::map<string,string>::value_type(name, value));
		}

		m_conditions.push_back(condition);
	}
}