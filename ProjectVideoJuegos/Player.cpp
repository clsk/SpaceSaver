#include "Player.h"

#include "stdafx.h"
#include <Windows.h>

#include "keyboard.h"
#include "GraphicManager.h"
#include "Game.h"

using namespace std;

Player::Player(ticpp::Element* xml_element) : GraphicObject(xml_element), m_angle_seq(0), m_SPRITE_INTERVAL_X(0.0f), m_SPRITE_INTERVAL_Y(0.083f)
{
	m_xml_element->GetAttribute("FrameDelay", &m_frame_delay);
}

void Player::update(float lfTimeStep)
{
	Keyboard& keyboard = Game::get_instance().m_keyboard;
	Scene& scene = (*Game::get_instance().get_scene());
	int liYaux, liXaux;

	// Handle rotations
	if ((keyboard.get_modifiers() & GLUT_ACTIVE_SHIFT) == GLUT_ACTIVE_SHIFT)
	{
		if (keyboard.check(eKey_Left))
		{
			if (m_angle_seq > 1)
			{
				--m_angle_seq;
			}
			else
			{
				m_angle_seq = (m_ROTATION_ANGLES-1);
			}
		}
		else if (keyboard.check(eKey_Right))
		{
			if(m_angle_seq < (m_ROTATION_ANGLES -1))
			{
				++m_angle_seq;
				
			}	
			else
			{
				m_angle_seq = 0;
			}
		}

		// If shift+direction is pressed, we're only rotating. so don't attempt to handle x,y axis movement
		return;
	}

	// Handle moving across scene (x,y axis movement)
	if(keyboard.check(GLUT_KEY_LEFT))	
	{
		if( (m_pos.x % scene.get_tile_size()) == 0)
		{
			liXaux = m_pos.x;
			m_pos.x -= m_STEP_LENGTH;
			if(m_pos.x<=0)
			{
				m_pos.x = liXaux;
			}	
			else
			{
				m_pos.x -= m_STEP_LENGTH;
			}
		}
		else
		{
			m_pos.x -= m_STEP_LENGTH;
		}
	}

	if(keyboard.check(GLUT_KEY_RIGHT))	
	{
		if( (m_pos.x % scene.get_tile_size()) == 0)
		{
			liXaux = m_pos.x;
			liXaux = m_pos.x += m_STEP_LENGTH;
			if((liXaux = m_pos.x+m_size.x)>=(scene.get_dimensions().x))
			{
				m_pos.x = liXaux;
			}
		}	
		else
		{
			m_pos.x +=m_STEP_LENGTH;
		}
	}
}

void Player::render(GraphicManager &graphic_manager)
{
	Scene* scene = Game::get_instance().get_scene();
	//determinar la posición en la pantalla donde se pintará
	int liScreen_X,liScreen_Y;
	liScreen_X = m_pos.x + scene->get_initial_pos().x;
	liScreen_Y = (m_pos.y)  + scene->get_initial_pos().y + (scene->get_block_size() - scene->get_tile_size());
	
	//renderizar el objeto
	float xo, yo, xf, yf;

	xo = 0.0f;
	yo = m_angle_seq != m_ROTATION_ANGLES ? (m_angle_seq*m_SPRITE_INTERVAL_Y) + m_SPRITE_INTERVAL_Y : 1.0f;

	xf = xo + 0.167f; 
	yf = yo - 0.083f;
	graphic_manager.DrawObject(m_texture.getID(), m_size.x, m_size.y, xo, yo, xf, yf,liScreen_X,liScreen_Y);
}
