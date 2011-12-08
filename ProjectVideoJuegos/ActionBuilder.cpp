#include "ActionBuilder.h"

#include "stdafx.h"
#include <string>
#include <map>
#include <cassert>

using std::string;

void ActionBuilder::build()
{
	ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(m_action_elements); child != child.end(); child++)
	{
		string type;
		child->GetValue(&type);
		Action* action = NULL;
		if (type == "Exit")
			action = new ExitAction;
		else if (type == "NextLevel")
			action = new NextLevelAction;
		else if (type == "Message")
			action = new MessageAction;
		else if (type == "Remove")
			action = new RemoveAction;
		else if (type == "Move")
			action = new MoveAction;
		else if (type == "Sleep")
			action = new SleepAction;

		assert(action != NULL);

		// Get parameters (XML Attributes)
		ticpp::Iterator< ticpp::Attribute > attribute;        
		for(attribute = attribute.begin(child.Get()); attribute != attribute.end(); attribute++)       
		{
			string name;
			string value;
			attribute->GetName(&name);            
			attribute->GetValue(&value);
			action->parameters.insert(std::map<string,string>::value_type(name, value));
		}

		m_actions.push_back(action);
	}
}