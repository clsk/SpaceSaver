#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <list>

#include "keyboard.h"
#include "GraphicManager.h"
#include "Scene.h"

#define GAME_DISPLAY_MENU	0
#define GAME_PLAYING		1
#define GAME_LOST			2
#define GAME_WON			3
#define GAME_TERMINATED		4

//Indica el tiempo máximo a esperar entre los updates
const float kfTimeLimit=0.1f; 

class Game
{
public:
	static Game& get_instance() 
	{ 
		if (m_instance == NULL) 
			m_instance = new Game();

		return *m_instance;
	}

	void end_game()
	{
		if (m_scene != NULL)
			delete m_scene;
	}

	void update(float);
	void render();
	void load_scene(const std::string& xml_file) { if (m_scene != NULL) delete m_scene; m_scene = new Scene(xml_file); }
	Scene* get_scene() { return m_scene; }
	void load_next_level();

	int status;
	Keyboard			m_keyboard;
	GraphicManager		m_graphics;

private:
	friend class Scene;
	Game();
	static Game*		m_instance;	
	float				m_accumulated_time;	//variable utilizada para controlar la velocidad

	Scene*				m_scene;
};



#endif // GAME_H