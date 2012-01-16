#include "Map.h"

#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include <cassert>

#include "GraphicManager.h"

using namespace std;

/*
bool Map::push_row(const char* line, size_t len)
{
	if (m_current_push_row >= ki_CONSOLE_DIMY || len > ki_CONSOLE_DIMX)
		return false;

	memcpy(m_screen+(m_current_push_row*ki_CONSOLE_DIMX), line, len);
	m_current_push_row++;
	return true;
}

bool Map::point_collides(const Point<>& point)
{
	return m_screen[(point.y*ki_CONSOLE_DIMX)+point.x] != ' ';
}

void Map::remove_obstacle(const Point<>& point)
{
	m_screen[(point.y*ki_CONSOLE_DIMX)+point.x] = ' ';
}

void Map::render(GraphicManager& graphic_manager)
{
	graphic_manager.WriteToBuffer(m_screen);
}
*/