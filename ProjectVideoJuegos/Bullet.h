#ifndef _BULLET_H
#define _BULLET_H

#include <string>

#include "GraphicManager.h"
#include "GraphicObject.h"
#include "Texture.h"
#include "ShooterInterface.h"

class Player;

class Bullet : public GraphicObject
{
public:
	Bullet(ShooterInterface* shooter, const Point<>& pos, int angle);
	bool update_bullet(float lfTimeStep);
	void render(GraphicManager& graphic_manager)
	{
		GraphicObject::render(graphic_manager);
	}

	static const int size = 16; // 16x16

private:
	friend class Player;
	ShooterInterface*	m_shooter;
	int					m_angle_seq;
	static bool			load_image(const std::string& image_path);
	static Texture		m_texture;

	inline int calc_vertical_mov_y()
	{
		if (m_angle_seq < 4)
			return 3 - m_angle_seq;
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
};

#endif // _BULLET_H