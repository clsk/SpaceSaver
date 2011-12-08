#include "Action.h"

#include "stdafx.h"
#include <map>
#include <string>
#include <cstdlib>
#include <Windows.h>

#include "Game.h"
#include "GraphicManager.h"
#include "GraphicObject.h"

using std::map;
using std::string;

typedef map<string,string>::iterator ParameterIterator;
#define ASSERT_PARAMETER(parameter) assert(parameter != parameters.end())

void ExitAction::act()
{
	Game::get_instance().status = GAME_TERMINATED;
}

void MoveAction::act()
{
	ParameterIterator name_iterator = parameters.find("name");
	ParameterIterator cellId_iterator = parameters.find("cellId");

	ASSERT_PARAMETER(name_iterator);
	ASSERT_PARAMETER(cellId_iterator);

	int cellId = atoi(cellId_iterator->second.c_str());
	
	GraphicObject* object = Game::get_instance().get_scene()->find_graphic_object(name_iterator->second);
	GraphicObject* move_to = Game::get_instance().get_scene()->find_graphic_object(cellId);

	object->set_position(move_to->get_position());
}

void MessageAction::act()
{
	/*
	ParameterIterator text_iterator = parameters.find("text");
	Game::get_instance().m_graphics.SetColor(eRed, eBlack);
	Game::get_instance().m_graphics.WriteChars(ki_CONSOLE_DIMX/4, ki_CONSOLE_DIMY/2, text_iterator->second.c_str());
	Game::get_instance().m_graphics.SwapBuffer();
	*/
}

void RemoveAction::act()
{
	ParameterIterator name_iterator = parameters.find("name");
	ASSERT_PARAMETER(name_iterator);

	Game::get_instance().get_scene()->remove_graphic_object(name_iterator->second);
}

void NextLevelAction::act()
{
	Game::get_instance().status = GAME_WON;
}

void SleepAction::act()
{
	ParameterIterator seconds_iterator = parameters.find("seconds");
	ASSERT_PARAMETER(seconds_iterator);
	int seconds = atoi(seconds_iterator->second.c_str()) * 1000;
	Sleep(seconds);
};