#include "Scene.h"

#include <list>
#include <string>
#include <iostream>
#include <climits>

#include "GraphicObject.h"
#include "Player.h"
#include "ticpp.h"
#include "RuleBuilder.h"
#include "Game.h"

using namespace std;

Scene::Scene(const std::string& xml_file) : m_xml_file(xml_file), m_xml_doc(xml_file), m_loaded(false), m_last_saved(0), m_points(0), m_score_board(Point<>(0,0))
{
	load_xml();
}

void Scene::update(float lfTimeStep)
{
	// Update Graphic Objects
	for (list<GraphicObject*>::iterator Iter = m_graphic_objects.begin(); Iter != m_graphic_objects.end(); ++Iter)
		(*Iter)->update(lfTimeStep);

	// Execute Rules
	for(list<Rule*>::iterator Iter = m_rules.begin(); Iter != m_rules.end(); ++Iter)
		(*Iter)->execute();

	// Update Score Board
	m_score_board.update(m_lives, m_points, m_level);

	/*
	if (Game::get_instance().m_keyboard.Pressed(eKey_F2) && (timeGetTime() - m_last_saved) > 5000)
	{
		// m_keyboard
		Game::get_instance().m_graphics.ClearScreen();
		Game::get_instance().m_graphics.WriteChars(0, 1, "Enter above the name you want to give to this saved game");
		Game::get_instance().m_graphics.SwapBuffer();
		string name = Game::get_instance().m_keyboard.ReadLine();
		name += "_saved.xml";
		set_xml_file(name);
		save();
		m_last_saved = timeGetTime();
	}
	*/
}

void Scene::render(GraphicManager &graphics)
{
	// Draw Background
	graphics.DrawObject(m_back_texture.getID(), m_dimensions.x, m_dimensions.y, 0.0f, 1.0f, 1.0f, 0.0f, 0, 0);

	// m_map.render(graphics);

	for (list<GraphicObject*>::iterator Iter = m_graphic_objects.begin(); Iter != m_graphic_objects.end(); ++Iter)
		(*Iter)->render(graphics);

	// Draw Score Board
	m_score_board.render(graphics);
}

Scene::~Scene()
{
	// Delete graphic objects
	for (list<GraphicObject*>::iterator Iter = m_graphic_objects.begin(); Iter != m_graphic_objects.end(); ++Iter)
		delete *Iter;

	// Delete rules
	for (list<Rule*>::iterator Iter = m_rules.begin(); Iter != m_rules.end(); ++Iter)
		delete *Iter;
}

/*
void Scene::load_map(ticpp::Iterator<ticpp::Element>& map_element)
{
	try
	{
		ticpp::Iterator<ticpp::Element> child;
		for(child = child.begin(map_element.Get()); child != child.end(); child++)
			m_map.push_row(child->GetText());
	}
	catch (ticpp::Exception& ex)
	{
		cout << ex.what() << endl;
	}
}
*/

void Scene::load_rules(ticpp::Iterator<ticpp::Element>& rule_element)
{
	try
	{
		ticpp::Iterator<ticpp::Element> child;
		for(child = child.begin(rule_element.Get()); child != child.end(); child++)
		{
			RuleBuilder rule_builder(child);
			rule_builder.build();

			m_rules.push_back(rule_builder.get_rule());
		}
	}
	catch (ticpp::Exception& ex)
	{
		cout << ex.what() << endl;
	}
}

void Scene::load_graphic_objects(ticpp::Iterator<ticpp::Element>& map_element)
{
	try
	{
		ticpp::Iterator<ticpp::Element> child;
		for(child = child.begin(map_element.Get()); child != child.end(); child++)
		{
			string type;
			child->GetAttribute("type", &type);

			GraphicObject* graphic_object = NULL;
			if (type == "Player")
			{
				graphic_object = dynamic_cast<GraphicObject*>(new Player(child.Get()));
			}
			else
			{
				graphic_object = new GraphicObject(child.Get());
			}

			m_graphic_objects.push_back(graphic_object);
			m_cells.insert(map<int, GraphicObject*>::value_type(graphic_object->get_cellID(), graphic_object));
		}
	}
	catch (ticpp::Exception& ex)
	{
		cout << ex.what() << endl;
	}
}

void Scene::load_xml()
{
	try 
	{
		m_xml_doc.LoadFile();

		// Read Scene properties
		m_xml_doc.FirstChildElement()->GetAttribute("number", &m_level);
		m_xml_doc.FirstChildElement()->GetAttribute("width", &(m_dimensions.x));
		m_xml_doc.FirstChildElement()->GetAttribute("height", &(m_dimensions.y));
		m_xml_doc.FirstChildElement()->GetAttribute("BlockSize", &(m_block_size));
		m_xml_doc.FirstChildElement()->GetAttribute("TileSize", &(m_tile_size));
		m_xml_doc.FirstChildElement()->GetAttribute("Lives", &m_lives);

		m_back_texture.load(m_xml_doc.FirstChildElement()->GetAttribute("background").c_str());
        ticpp::Iterator<ticpp::Element> child;
        for(child = child.begin(m_xml_doc.FirstChildElement()); child != child.end(); child++)
        {
                std::string name;
                child->GetValue(&name);
//				if (name == "Map")
//					load_map(child);
				if (name == "SpecialCells")
					load_graphic_objects(child);
				else if (name == "Rules")
					load_rules(child);
        }
		m_loaded = true;
	}
	catch(ticpp::Exception& ex)
	{
		Game::get_instance().status = GAME_DISPLAY_MENU;
		Game::get_instance().m_scene = NULL;
	}
}

GraphicObject* Scene::find_graphic_object(const std::string& name)
{
	for (list<GraphicObject*>::iterator Iter = m_graphic_objects.begin(); Iter != m_graphic_objects.end(); ++Iter)
		if ((*Iter)->get_name() == name)
			return *Iter;

	return NULL;
}

GraphicObject* Scene::find_graphic_object(int cellId)
{
	std::map<int, GraphicObject*>::iterator Iter = m_cells.find(cellId);
	return Iter != m_cells.end() ? Iter->second : NULL;
}

bool Scene::remove_graphic_object(const std::string& name)
{
	for (list<GraphicObject*>::iterator Iter = m_graphic_objects.begin(); Iter != m_graphic_objects.end(); ++Iter)
	{
		if ((*Iter)->get_name() == name)
		{
			delete *Iter;
			m_graphic_objects.erase(Iter);
			return true;
		}
	}

	return false;
}

bool Scene::remove_graphic_object(int cellId)
{
	std::map<int, GraphicObject*>::iterator Iter = m_cells.find(cellId);
	if (Iter != m_cells.end())
	{
		m_cells.erase(Iter);
		return true;
	}
	else
	{
		return false;
	}
}