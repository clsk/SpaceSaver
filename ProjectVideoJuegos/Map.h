#ifndef _MAP_H
#define _MAP_H

#include <string>
#include <utility>

#include "GraphicManager.h"

class Map
{
public:
	Map (Point<> dimensions) : m_current_push_row(0) {}

	/**
	 *  @description 
	 */
	void render(GraphicManager& graphic_manager);
	bool point_collides(const Point<>& point);
	bool point_collides(const Point<float>& point) { return point_collides(Point<>((int)point.x, (int)point.y)); }
	void remove_obstacle(const Point<>& point);
	bool push_row(const char* line, size_t len);
	bool push_row(const std::string& line) { return push_row(line.c_str(), line.length()); }

	// Accessors
	// Point<> get_start() const { return m_start_pos; }
	// Point<> get_end() const { return m_end_pos; }

private:
	char*	m_screen;
	size_t	m_current_push_row;
};

#endif _MAP_H