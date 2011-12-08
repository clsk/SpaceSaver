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
	Player(ticpp::Element* xml_element);

	/*
	 *  @brief
	 *  @param K objeto del KeyboardManager
	 *  @param lfTimeStep tiempo transcurrido
	 */
	void update(float lfTimeStep);

	void render(GraphicManager &graphic_manager);

protected:
	static const int	m_STEP_LENGTH = 2;
	static const int	m_ROTATION_ANGLES = 12;
	const float			m_SPRITE_INTERVAL_X;
	const float			m_SPRITE_INTERVAL_Y;
	int					m_frame_delay;
	int					m_angle_seq;
	int					m_delay;
};


#endif // PLAYER_H