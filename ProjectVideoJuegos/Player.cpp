#include "Player.h"

#include "stdafx.h"
#include <Windows.h>

#include "keyboard.h"
#include "GraphicManager.h"
#include "Game.h"

using namespace std;

void Player::update(float lfTimeStep)
{
	Keyboard& keyboard = Game::get_instance().m_keyboard;
	Scene& scene = (*Game::get_instance().get_scene());
	int liYaux, liXaux;
	if(keyboard.check(GLUT_KEY_LEFT))	
	{
		if( (m_pos.x % scene.get_tile_size()) == 0)
		{
		liXaux = m_pos.x;
		m_pos.x -= kiSTEP_LENGTH;
		if(m_pos.x<=0)
			{
				m_pos.x = liXaux;
				lsScene->msPlayer.miState = eSTATE_LOOKLEFT;
			}
		}	
		else
		{
		m_pos.x -=kiSTEP_LENGTH;
		if( lsScene->msPlayer.miState != eSTATE_WALKLEFT )
			{
				lsScene->msPlayer.miState = eSTATE_WALKLEFT;
				lsScene->msPlayer.miSeq = 0;
				lsScene->msPlayer.miDelay = 0;
			}
		}
	}
	else if(lsKeyBoard->mabKeys[GLUT_KEY_RIGHT])	
	{
		if( (m_pos.x % lsScene->miTILE_SIZE) == 0)
		{
		liXaux = lsScene->msPlayer.miX;
		lsScene->msPlayer.miX+= kiSTEP_LENGTH;
		if((lsScene->msPlayer.miX+lsScene->msPlayer.miW)>=(lsScene->miSCENE_WIDTH))
			{
				lsScene->msPlayer.miX = liXaux;
				lsScene->msPlayer.miState = eSTATE_LOOKRIGHT;
			}
		}	
		else
		{
		lsScene->msPlayer.miX +=kiSTEP_LENGTH;
		if( lsScene->msPlayer.miState != eSTATE_WALKRIGHT )
			{
				lsScene->msPlayer.miState = eSTATE_WALKRIGHT;
				lsScene->msPlayer.miSeq = 0;
				lsScene->msPlayer.miDelay = 0;
			}
		}
}

void Player::render(GraphicManager &graphic_manager)
{
	Scene* scene = Game::get_instance().get_scene();
	//determinar la posición en la pantalla donde se pintará
	int liScreen_X,liScreen_Y;
	liScreen_X = m_pos.x + scene->get_initial_pos().x;
	liScreen_Y = (m_pos.y)  + scene->get_initial_pos().y + (scene->get_block_size() - scene->get_tile_size());
	
	//renderizar el objeto

	float xo, yo, xf, yf;
	xo = 0.0f; yo = 1.0f;
	xf = xo + 0.167f; 
	yf = yo - 0.083f;
	graphic_manager.DrawObject(m_texture.getID(), m_size.x, m_size.y, 0.0f, 0.1f, 0.1f, 0.0f,liScreen_X,liScreen_Y);
}
