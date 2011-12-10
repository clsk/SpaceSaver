#ifndef _SCENE_H
#define _SCENE_H

#include <list>
#include <map>
#include <string>

#include "Player.h"
#include "GraphicObject.h"
#include "ticpp.h"
#include "Rule.h"
#include "Texture.h"
#include "ScoreBoard.h"

class Scene
{
public:
	Scene(const std::string& xml_file);
	~Scene();
	void render(GraphicManager &graphics);
	void update(float lfTimeStep);
	void load_xml();
	void set_xml_file(const std::string& xml_file) { m_xml_file = xml_file; } 
	void save() { m_xml_doc.SaveFile(m_xml_file); }

	// Getters
	// Map& get_map() { return m_map; }
	size_t get_level() const { return m_level; }
	const Point<>& get_initial_pos() { return m_initial_pos; }
	const Point<>& get_dimensions() { return m_dimensions; }
	int get_block_size() { return m_block_size; }
	int get_tile_size() { return m_tile_size; }

	GraphicObject* find_graphic_object(const std::string& name);
	GraphicObject* find_graphic_object(int cellId);

	bool remove_graphic_object(const std::string& name);
	bool remove_graphic_object(int cellId);

	// Lives
	int get_lives() const { return m_lives; }
	int add_lives(int interval) { m_lives += interval; return m_lives; }

private:
	// void load_map(ticpp::Iterator<ticpp::Element>& map_element);
	void load_graphic_objects(ticpp::Iterator<ticpp::Element>& map_element);
	void load_rules(ticpp::Iterator<ticpp::Element>& rule_element);
	bool							m_loaded;
	size_t							m_level;
	ticpp::Document					m_xml_doc;
	// Map								m_map;
	std::list<GraphicObject*>		m_graphic_objects;
	std::map<int, GraphicObject*>	m_cells; // Graphic objects indexed by cell number
	std::list<Rule*>				m_rules;
	std::string						m_xml_file;
	float							m_last_saved;
	int								m_tile_size;
	int								m_block_size;
	Point<>							m_dimensions;
	Point<>							m_initial_pos;
	Texture							m_back_texture;
	ScoreBoard						m_score_board;
	int								m_lives;
	int								m_points;
};

#endif // _SCENE_H