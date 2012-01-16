#include "Bullet.h"
#include "Texture.h"
#include "Game.h"

#include <cstdio>
#include <string>

using std::string;

Bullet::Bullet(ShooterInterface* shooter, const Point<>& pos, int angle) : GraphicObject(pos, Point<>(14,36), &m_texture), m_shooter(shooter), m_angle_seq(angle)
{

}

bool Bullet::update_bullet(float lfTimeStep)
{
	m_pos.x += calc_vertical_mov_x() << 2;
	m_pos.y += calc_vertical_mov_y() << 2;

	const Point<>& scene_dim = Game::get_instance().get_scene()->get_dimensions();
	if (m_pos.x <= 0 || m_pos.x >= scene_dim.x || m_pos.y <= 0 || m_pos.y >= scene_dim.y)
		return false;

	return true;
}

bool Bullet::load_image(const string& image_path)
{
	return m_texture.load(image_path.c_str(), GL_RGBA);
}

Texture Bullet::m_texture = Texture();