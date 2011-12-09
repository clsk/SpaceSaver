#include "GraphicObject.h"

#include <string>

#include "stdafx.h"
#include "Game.h"
#include "Scene.h"

using std::string;

GraphicObject::GraphicObject(ticpp::Element* xml_element) : m_xml_element(xml_element)
{
	m_xml_element->GetAttribute("cellId", &m_cellID);
	m_xml_element->GetAttribute("posX", &(m_pos.x));
	m_xml_element->GetAttribute("posY", &(m_pos.y));
	m_xml_element->GetAttribute("name", &m_name);
	m_xml_element->GetAttribute("width", &(m_size.x));
	m_xml_element->GetAttribute("height", &(m_size.y));

	string image_path;
	m_xml_element->GetAttribute("ImagePath", &image_path);

	m_texture.load(image_path.c_str(), GL_RGBA);
}

GraphicObject::GraphicObject(const Point<>& pos, const Point<>& size, const string& image_path) : m_xml_element(NULL), m_pos(pos), m_size(size)
{
	m_texture.load(image_path.c_str(), GL_RGBA);
}

void GraphicObject::render(GraphicManager &graphic_manager)
{
	Scene* scene = Game::get_instance().get_scene();
	//determinar la posición en la pantalla donde se pintará
	int liScreen_X,liScreen_Y;
	liScreen_X = m_pos.x + scene->get_initial_pos().x;
	liScreen_Y = (m_pos.y)  + scene->get_initial_pos().y + (scene->get_block_size() - scene->get_tile_size());
	
	//renderizar el objeto (paint whole image)
	graphic_manager.DrawObject(m_texture.getID(), m_size.x, m_size.y, 0.0f, 1.0f, 1.0f, 0.0f,liScreen_X,liScreen_Y);
}