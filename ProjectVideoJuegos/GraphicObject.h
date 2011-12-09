#ifndef _GRAPHICOBJECT_H
#define _GRAPHICOBJECT_H

#include "GraphicManager.h"

#include <string>

#include "stdafx.h"
#include "ticpp.h"
#include "Texture.h"

/**
    Definición de los estados en objectos en movimiento
*/
enum ObjectState
{
	eSTATE_LOOKLEFT=0,
	eSTATE_LOOKRIGHT,		
	eSTATE_WALKLEFT,		
	eSTATE_WALKRIGHT,	
	eSTATE_LOOKUP,
	eSTATE_LOOKDOWN,		
	eSTATE_WALKUP,		
	eSTATE_WALKDOWN		
};

/*
 *  @brief Esta clase representa un objeto grafico en el juego
 */
class GraphicObject
{
public:


	/*
	 *  @brief Constructor
	 */
	GraphicObject(ticpp::Element* xml_element);

	GraphicObject(const Point<>& pos, const Point<>& size, const std::string& image_path);

	virtual ~GraphicObject() {};

	/*
	 *  @brief
	 *  @param K objeto del KeyboardManager
	 *  @param lfTimeStep tiempo transcurrido
	 */
	virtual void update(float lfTimeStep)  {};

	/*
	 *  @brief Renderizador del jugador
	 *  @param graphic_manager Manejador de graficos del juego
	 */
	virtual void render(GraphicManager &graphic_manager);

	// Setters
	virtual void set_position(const Point<>& pos) { m_pos = pos; update_xml_pos(); }

	// Getters
	virtual int get_imageID() { return m_texture.getID(); }
	virtual const Point<>& get_size() const { return m_size; }
	virtual const Point<>& get_position() const { return m_pos; }
	virtual const std::string& get_name() const { return m_name; }
	virtual int get_cellID() const { return m_cellID; }

protected:
	virtual void update_xml_pos() 
	{ 
		if (m_xml_element) 
		{ 
			m_xml_element->SetAttribute("posX", m_pos.x); 
			m_xml_element->SetAttribute("posY", m_pos.y); 
		} 
	}

	ticpp::Element*	m_xml_element;
	int				m_cellID;
	std::string		m_name;
	Point<>			m_pos;
	Point<>			m_size;
	Texture			m_texture;

};

#endif // _GRAPHICOBJECT_H