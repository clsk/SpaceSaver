#include "GraphicObject.h"

#include <string>

#include "Game.h"
#include "Scene.h"

using std::string;

GraphicObject::GraphicObject(ticpp::Element* xml_element, Texture* texture) : m_xml_element(xml_element), m_texture_ptr(texture)
{
	m_xml_element->GetAttribute("cellId", &m_cellID);
	m_xml_element->GetAttribute("posX", &(m_pos.x));
	m_xml_element->GetAttribute("posY", &(m_pos.y));
	m_xml_element->GetAttribute("name", &m_name);
	m_xml_element->GetAttribute("width", &(m_size.x));
	m_xml_element->GetAttribute("height", &(m_size.y));
}

GraphicObject::GraphicObject(const Point<>& pos, const Point<>& size, Texture* texture) 
	: m_xml_element(NULL), m_pos(pos), m_size(size), m_texture_ptr(texture)
{
}

void GraphicObject::render(GraphicManager &graphic_manager)
{
	// If this object doesn't have a texture, don't draw anything
	if (m_texture_ptr == NULL)
		return;

	Scene* scene = Game::get_instance().get_scene();
	//determinar la posición en la pantalla donde se pintará
	int liScreen_X,liScreen_Y;
	liScreen_X = m_pos.x + scene->get_initial_pos().x;
	liScreen_Y = (m_pos.y)  + scene->get_initial_pos().y + (scene->get_block_size() - scene->get_tile_size());
	
	//renderizar el objeto (paint whole image)
	graphic_manager.DrawObject(m_texture_ptr->getID(), m_size.x, m_size.y, 0.0f, 1.0f, 1.0f, 0.0f,liScreen_X,liScreen_Y);
}