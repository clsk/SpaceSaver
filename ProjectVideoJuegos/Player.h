#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "GraphicManager.h"
#include "GraphicObject.h"
#include "keyboard.h"
#include "ticpp.h"

#include <list>


/*
 *  @brief Esta clase representa al jugador
 */
class Player : public GraphicObject
{
public:
	/*
	 *  @brief Constructor
	 */
	Player(ticpp::Element* xml_element) : GraphicObject(xml_element) 
	{
		m_xml_element->GetAttribute("FrameDelay", &m_frame_delay);
	}

	/*
	 *  @brief
	 *  @param K objeto del KeyboardManager
	 *  @param lfTimeStep tiempo transcurrido
	 */
	void update(float lfTimeStep);

	void render(GraphicManager &graphic_manager);

protected:
	int m_frame_delay;
};


#endif // PLAYER_H