#ifndef PLAYER_H
#define PLAYER_H

#include "GraphicManager.h"
#include "GraphicObject.h"
#include "keyboard.h"
#include "ticpp.h"
#include "Bullet.h"
#include "ShooterInterface.h"

#include <list>
#include <string>

/*
 *  @brief Esta clase representa al jugador
 */
class Player : public GraphicObject, public ShooterInterface
{
public:
	/*
	 *  @brief Constructor
	 */
	Player(ticpp::Element* xml_element);

	/*
	 *  @brief
	 *  @param K objeto del KeyboardManager
	 *  @param lfTimeStep tiempo transcurrido
	 */
	void update(float lfTimeStep);
	void render(GraphicManager &graphic_manager);
	static const Texture& get_texture()
	{
		return m_texture;
	}

	// Implementation of ShooterInterface
	void remove_bullet(Bullet* bullet)
	{
		m_bullets.remove(bullet);
		delete bullet;
	}

protected:
	static bool load_image(const std::string& image_path);
	inline int calc_vertical_mov_y()
	{
		if (m_angle_seq < 4)
			return m_STEP_LENGTH - m_angle_seq;
		else
			return m_angle_seq - 9;
	}

	inline int calc_vertical_mov_x()
	{
		if (m_angle_seq < 4)
			return m_angle_seq;
		else if (m_angle_seq == 10)
			return -2;
		else if (m_angle_seq == 11)
			return -1;
		else
			return 6 - m_angle_seq;
	}

	inline int calc_horizontal_mov_x() { return calc_vertical_mov_y(); }
	inline int calc_horizontal_mov_y() { return calc_vertical_mov_x(); }

	static const int	m_STEP_LENGTH = 3;
	static const int	m_ROTATION_ANGLES = 12;
	const float			m_SPRITE_INTERVAL_X;
	const float			m_SPRITE_INTERVAL_Y;
	int					m_frame_delay;
	int					m_angle_seq;
	int					m_delay;
	std::list<Bullet*>	m_bullets;
	time_t				m_last_shot;
	static Texture		m_texture;
};


#endif // PLAYER_H