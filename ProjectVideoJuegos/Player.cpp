#include "Player.h"

#include <ctime>

#include "keyboard.h"
#include "GraphicManager.h"
#include "Game.h"

using namespace std;

Player::Player(ticpp::Element* xml_element) : GraphicObject(xml_element), m_angle_seq(0), m_SPRITE_INTERVAL_X(0.0f), m_SPRITE_INTERVAL_Y(0.083f), m_last_shot(time(NULL))
{
	m_xml_element->GetAttribute("FrameDelay", &m_frame_delay);
	string image_path;
	m_xml_element->GetAttribute("ImagePath", &image_path);
	load_image(image_path);
	// Reuse image_path for bullet image
	m_xml_element->GetAttribute("BulletImage", &image_path);
	Bullet::load_image(image_path);
}

void Player::update(float lfTimeStep)
{
	Keyboard& keyboard = Game::get_instance().m_keyboard;
	Scene& scene = (*Game::get_instance().get_scene());

	// Update bullets
	for (std::list<Bullet*>::iterator Iter = m_bullets.begin(); Iter != m_bullets.end(); )
	{
		// Bullet has gone out of scene bounds, delete it
		if ((*Iter)->update_bullet(lfTimeStep) == false)
		{
			delete *Iter;
			Iter = m_bullets.erase(Iter);
		}
		else
			++Iter;
	}

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
		else if (keyboard.check(VK_SPACE))
		{
			// Hell fire
			// Limit shots to one per second
			time_t current_time = time(NULL);
			if (current_time - m_last_shot > 0)
			{
				m_last_shot = current_time;
				for (unsigned int i = 0; i < m_ROTATION_ANGLES; ++i)
					m_bullets.push_back(new Bullet(dynamic_cast<ShooterInterface*>(this), Point<>(m_pos.x+(m_size.x/2)-Bullet::size, m_pos.y+m_size.y+1), i));
			}
		}

		// If shift+direction is pressed, we're only rotating. so don't attempt to handle x,y axis movement
		return;
	}

	// Handle moving across scene (x,y axis movement)
	if(keyboard.check(GLUT_KEY_LEFT))	
	{
		if (m_pos.x > 0)
		{
			m_pos.x -= calc_horizontal_mov_x()<<1;
			m_pos.y += calc_horizontal_mov_y()<<1;
		}
	} 

	if(keyboard.check(GLUT_KEY_RIGHT))	
	{
		if (m_pos.x < scene.get_dimensions().x)
		{
			m_pos.x += calc_horizontal_mov_x()<<1;
			m_pos.y -= calc_horizontal_mov_y()<<1;
		}
	}

	if(keyboard.check(GLUT_KEY_UP))
	{
		if (m_pos.y < scene.get_dimensions().y)
		{
			m_pos.x += calc_vertical_mov_x()<<1;
			m_pos.y += calc_vertical_mov_y()<<1;
		}
	}

	if(keyboard.check(GLUT_KEY_DOWN))
	{
		if (m_pos.y > 0)
		{
			m_pos.x -= calc_vertical_mov_x() <<1;
			m_pos.y -= calc_vertical_mov_y() <<1;
		}
	}

	if (keyboard.check(VK_SPACE))
	{
		// Limit shots to one per second
		time_t current_time = time(NULL);
		if (current_time - m_last_shot > 0)
		{
			m_last_shot = current_time;
			m_bullets.push_back(new Bullet(dynamic_cast<ShooterInterface*>(this), Point<>(m_pos.x+(m_size.x/2)-Bullet::size, m_pos.y+m_size.y+1), m_angle_seq));
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

	// Render Bullets
	for (std::list<Bullet*>::iterator Iter = m_bullets.begin(); Iter != m_bullets.end(); ++Iter)
	{
		(*Iter)->render(graphic_manager);
	}
}

bool Player::load_image(const string& image_path)
{
	return m_texture.load(image_path.c_str(), GL_RGBA);
}

Texture Player::m_texture = Texture();
