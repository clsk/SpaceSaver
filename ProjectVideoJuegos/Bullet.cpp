#include "Bullet.h"
#include <cstdio>


Bullet::Bullet(const Point<>& pos) : GraphicObject(pos, Point<>(16,16), ".\\IMAGES\\fire.png")
{

}

void Bullet::update(float lfTimeStep)
{
	m_pos.y += 4;
}
