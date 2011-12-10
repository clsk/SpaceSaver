#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include "GraphicManager.h"

class ScoreBoard
{
public:
	ScoreBoard(const Point<>& pos);
	void update(int lives, int points, int level);
	void render(GraphicManager& graphic_manager);

private:
	Point<> m_pos; // position in screen;
	int		m_lives;
	int		m_points;
	int		m_level;

};

#endif // _SCOREBOARD_H