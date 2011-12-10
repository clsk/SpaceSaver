#include "ScoreBoard.h"
#include "Player.h"
#include "Game.h"
#include "Scene.h"

#include <string>

using std::string;

ScoreBoard::ScoreBoard(const Point<>& pos) :m_lives(0), m_points(0), m_level(0)
{
	// m_life.load(".\\IMAGES\\plus_life_128.png");
}

void ScoreBoard::update(int lives, int points, int level)
{
	m_lives = lives;
	m_points = points;
	m_level = level;
}

void ScoreBoard::render(GraphicManager& graphic_manager)
{
	Scene& scene = *(Game::get_instance().get_scene());

	// Draw Lives
	float xo = 0.0f;
	float yo = 0.038;
	float xf = 0.167f; 
	float yf = 0.0f;
	graphic_manager.DrawObject(Player::get_texture().getID(), 16, 16, xo, yo, xf, yf, 0 , scene.get_dimensions().y - 16);

	char characters[10];
	sprintf(characters, "%u", m_lives);
	graphic_manager.DrawMessage(characters, (m_pos.x + 16) , scene.get_dimensions().y - 15);

	// Draw Level
	sprintf(characters, "%u", m_level);
	string message = "Level ";
	message += characters;
	graphic_manager.DrawMessage(message, (scene.get_dimensions().x >> 1)-(message.length() << 4), scene.get_dimensions().y - 15);
	// graphic_manager.DrawObject(m_life.getID(), 16, 16, 0.0f, 0.25f, 0.25f, 0.0f, 32 , scene.get_dimensions().y - 64);

	// Draw Points
	sprintf(characters, "%u", m_points);
	message = characters;
	message += "Pts";
	graphic_manager.DrawMessage(message, scene.get_dimensions().x - (message.length() << 4) - 8, scene.get_dimensions().y - 15, GLUT_BITMAP_TIMES_ROMAN_10);
}