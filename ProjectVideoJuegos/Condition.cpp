#include "Condition.h"

#include <map>
#include <string>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "GraphicObject.h"
#include "Game.h"

using std::string;
using std::map;

typedef map<string,string>::iterator ParameterIterator;
#define ASSERT_PARAMETER(parameter) assert(parameter != parameters.end())

bool ContentCondition::evaluate()
{
	// assert arguments are there
	ParameterIterator cellId_iter = parameters.find("cellId");
	ParameterIterator name = parameters.find("name");

	ASSERT_PARAMETER(cellId_iter);
	ASSERT_PARAMETER(name);

	int cellId = atoi(cellId_iter->second.c_str());

	GraphicObject* obj_name = Game::get_instance().get_scene()->find_graphic_object(name->second);
	GraphicObject* obj_cellId = Game::get_instance().get_scene()->find_graphic_object(cellId);

	if ((int)obj_name->get_position().x == (int)obj_cellId->get_position().x &&
		(int)obj_name->get_position().y == (int)obj_cellId->get_position().y)
	{
		return true;
	}
	else
	{
		return false;
	}


}