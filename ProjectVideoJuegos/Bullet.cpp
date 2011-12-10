#include "Bullet.h"
#include "Texture.h"

#include <cstdio>
#include <string>

using std::string;

Bullet::Bullet(const Point<>& pos) : GraphicObject(pos, Point<>(14,36), &m_texture)
{

}

void Bullet::update(float lfTimeStep)
{
	m_pos.y += 4;
}

bool Bullet::load_image(const string& image_path)
{
	return m_texture.load(image_path.c_str(), GL_RGBA);
}

Texture Bullet::m_texture = Texture();