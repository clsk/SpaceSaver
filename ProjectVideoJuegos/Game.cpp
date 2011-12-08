#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <utility>
#include <cstdlib>
#include <sstream>

#include "stdafx.h"
#include "Game.h"
#include "Player.h"

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::make_pair;
using std::list;
using std::stringstream;

Game::Game() : status(GAME_DISPLAY_MENU), m_accumulated_time(0.0f), m_scene(NULL)
{
}

void Game::update(float lfTimeStep)
{
	if (m_keyboard.check(eKey_Esc))
		status = GAME_TERMINATED;

		//controlando la velocidad
    m_accumulated_time += lfTimeStep;
    if ( m_accumulated_time < kfTimeLimit )
        return;
    m_accumulated_time = 0.0f;

	m_scene->update(lfTimeStep);
}

void Game::render()
{
	//*****************************************************************************
	//Limpiar los buffers
	m_graphics.ClearBuffer();

	//Visualizar la escena
	m_scene->render(m_graphics);

	//Visualizar buffer
	m_graphics.SwapBuffer();
}

void Game::load_next_level()
{
		m_graphics.ClearBuffer();
		m_graphics.SwapBuffer();
		status = GAME_PLAYING;
		stringstream ss;
		ss << "Level" << m_scene->get_level()+1 << ".xml";
		Game::get_instance().load_scene(ss.str());
}

Game* Game::m_instance = NULL;