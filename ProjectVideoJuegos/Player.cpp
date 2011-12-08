#include "Player.h"

#include "stdafx.h"
#include <Windows.h>

#include "keyboard.h"
#include "GraphicManager.h"
#include "Game.h"

using namespace std;

void Player::update(float lfTimeStep)
{
	/*
	if (Game::get_instance().m_keyboard.Pressed(eKey_Right))
	{
		float new_pos = m_pos.x + (m_velocity.x * lfTimeStep);
		if (new_pos < ki_CONSOLE_DIMX &&
			Game::get_instance().get_scene()->get_map().point_collides(Point<float>(new_pos, m_pos.y)) == false)
		{
			m_pos.x = new_pos;
			GraphicObject::set_position(m_pos);
		}
	}

	if (Game::get_instance().m_keyboard.Pressed(eKey_Left))
	{
		float new_pos = m_pos.x - (m_velocity.x * lfTimeStep);
		if (new_pos > 0 &&
			Game::get_instance().get_scene()->get_map().point_collides(Point<float>(new_pos, m_pos.y)) == false)
		{
			m_pos.x = new_pos;
			GraphicObject::set_position(m_pos);
		}
	}

	if (Game::get_instance().m_keyboard.Pressed(eKey_Up))
	{
		float new_pos = m_pos.y - (m_velocity.y * lfTimeStep);
		if (new_pos > 0 &&
			Game::get_instance().get_scene()->get_map().point_collides(Point<float>(m_pos.x, new_pos)) == false)
		{
			m_pos.y = new_pos;
			GraphicObject::set_position(m_pos);
		}
	}

	if (Game::get_instance().m_keyboard.Pressed(eKey_Down))
	{
		float new_pos = m_pos.y + (m_velocity.y * lfTimeStep);
		if (new_pos > 0 &&
			Game::get_instance().get_scene()->get_map().point_collides(Point<float>(m_pos.x, new_pos)) == false)
		{
			m_pos.y = new_pos;
			GraphicObject::set_position(m_pos);
		}
	}
	*/
}
