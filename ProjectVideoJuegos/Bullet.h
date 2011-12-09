#ifndef _BULLET_H
#define _BULLET_H

#include "GraphicManager.h"
#include "GraphicObject.h"

class Bullet : public GraphicObject
{
public:
	Bullet(const Point<>& pos);
	void update(float lfTimeStep);
	void render(GraphicManager& graphic_manager)
	{
		GraphicObject::render(graphic_manager);
	}

	static const int size = 16; // 16x16
};

#endif // _BULLET_H