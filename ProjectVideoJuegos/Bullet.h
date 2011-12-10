#ifndef _BULLET_H
#define _BULLET_H

#include <string>

#include "GraphicManager.h"
#include "GraphicObject.h"
#include "Texture.h"

class Player;

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

private:
	friend class Player;
	static bool		load_image(const std::string& image_path);
	static Texture	m_texture;
};

#endif // _BULLET_H