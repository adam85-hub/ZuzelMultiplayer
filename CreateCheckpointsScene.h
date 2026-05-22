#pragma once
#include "Scene.h"
#include "ResourceManager.h"

#include <allegro5/allegro_primitives.h>
#include <vector>
#include <filesystem>
#include <fstream>
#include "vec2.h"

#include "LOG.h"

class CreateCheckpointsScene : public Scene {
public:
	CreateCheckpointsScene(GameCommands* gameCommands) : Scene(gameCommands) {
		al_show_mouse_cursor(al_get_current_display());

		ALLEGRO_BITMAP* race_track = al_load_bitmap("./Assets/track.png");
		_race_track = al_create_bitmap(c_RENDER_WIDTH, c_RENDER_HEIGHT);
		_resource_manager.Track_resource(_race_track);
		al_set_target_bitmap(_race_track);
		al_draw_scaled_bitmap(race_track, 0, 0, al_get_bitmap_width(race_track), al_get_bitmap_height(race_track), 0, 0, c_RENDER_WIDTH, c_RENDER_HEIGHT, 0);
		al_set_target_backbuffer(al_get_current_display());
	}

	void Update(KeyStatesTable key_states) {
		al_get_mouse_state(&_mouse_state);
		_cursor_pos.x = _mouse_state.x;
		_cursor_pos.y = _mouse_state.y;

		if (_points.size() > 0) {
			if (key_states[ALLEGRO_KEY_ALT] & c_KEY_DOWN or key_states[ALLEGRO_KEY_ALTGR] & c_KEY_DOWN) {
				_cursor_pos.y = _points[_points.size() - 1].y;
			}
			if (key_states[ALLEGRO_KEY_LSHIFT] & c_KEY_DOWN or key_states[ALLEGRO_KEY_RSHIFT] & c_KEY_DOWN) {
				_cursor_pos.x = _points[_points.size() - 1].x;
			}

			if (_points.size() % 2 == 0 and (_mouse_state.buttons & ALLEGRO_MOUSE_BUTTON_RIGHT)) {
				_multiple_mode = true;
			}

			if ((key_states[ALLEGRO_KEY_BACKSPACE] & c_KEY_PRESSED) and _points.size() > 0) {
				_points.pop_back();
			}

			if (key_states[ALLEGRO_KEY_ENTER] & c_KEY_PRESSED and _points.size() >= 2) {
				save_to_file("checkpoints.txt");
			}
		}		
		
		if (_multiple_mode and (_points.size() == 0 or _points.size() % 2 == 1)) {
			if (_mm_points.size() > 0)
				_mm_points.clear();

			_multiple_mode = false;
		}

		if ((_mouse_state.buttons & ALLEGRO_MOUSE_BUTTON_LEFT) and 
			(_points.size() == 0 or _points[_points.size() - 1].Distance(_cursor_pos.x, _cursor_pos.y) > _circle_radius * 3)) 
		{
			if (_multiple_mode) {
				_multiple_mode = false;
				for (auto point : _mm_points) {
					_points.push_back(point);
				}
				_mm_points.clear();
			}
			else
				_points.emplace_back(_cursor_pos.x, _cursor_pos.y);
		}

		if (_multiple_mode) {
			int delta_z = _last_z - _mouse_state.z;
			_mm_number_of_lines = std::max(2, _mm_number_of_lines - delta_z);
			_last_z = _mouse_state.z;

			Utils::vec2 a = _points[_points.size() - 1];
			Utils::vec2 b = _points[_points.size() - 2];
			Utils::vec2 line_vec = b - a;
			Utils::vec2 advance = (_cursor_pos - a) / _mm_number_of_lines;

			_mm_points.clear();
			_mm_points.reserve(_mm_number_of_lines);
			for (int i = 1; i <= _mm_number_of_lines; i++) {
				_mm_points.emplace_back(a + advance * i);
				_mm_points.emplace_back(a + advance * i + line_vec);
			}
		}

		
	}

	void Render() {
		al_draw_bitmap(_race_track, 0, 0, 0);

		int i = 0;
		for (; i < _points.size() / 2; i++) {
			Utils::vec2 a = _points[2 * i];
			Utils::vec2 b = _points[2 * i + 1];
			al_draw_filled_circle(a.x, a.y, _circle_radius, _color_line);
			al_draw_filled_circle(b.x, b.y, _circle_radius, _color_line);
			al_draw_line(a.x, a.y, b.x, b.y, _color_line, 2);
		}
		i = std::max(0, 2 * i);
		if (i < _points.size()) {
			Utils::vec2 a = _points[i];
			al_draw_filled_circle(a.x, a.y, _circle_radius, _color_line);
			al_draw_line(a.x, a.y, _cursor_pos.x, _cursor_pos.y, _color_line, 2);
		}

		for (i = 0; i < _mm_points.size() / 2; i++) {
			Utils::vec2 a = _mm_points[2 * i];
			Utils::vec2 b = _mm_points[2 * i + 1];
			al_draw_filled_circle(a.x, a.y, _circle_radius, _color_mm_line);
			al_draw_filled_circle(b.x, b.y, _circle_radius, _color_mm_line);
			al_draw_line(a.x, a.y, b.x, b.y, _color_mm_line, 2);
		}

		al_draw_filled_circle(_cursor_pos.x, _cursor_pos.y, _circle_radius, _color_cursor);
	} 

	void save_to_file(std::filesystem::path filename, std::vector<Utils::vec2>* points_to_save = nullptr) {
		if (points_to_save == nullptr)
			points_to_save = &_points;

		if (points_to_save->size() % 2 == 1)
			points_to_save->pop_back();

		std::ofstream output_file;
		output_file.open(filename, std::ios::out | std::ios::trunc);
		if (!output_file.is_open())
			throw std::runtime_error("Couldnt open file: " + filename.string());

		for (Utils::vec2 point : *points_to_save) {
			output_file << point.x << " " << point.y << ",";
		}

		output_file.close();
	}

	ALLEGRO_BITMAP* _race_track;
	std::vector<Utils::vec2> _points;
	int _circle_radius = 4;

	bool _multiple_mode = false;
	int _mm_number_of_lines = 4;
	std::vector<Utils::vec2> _mm_points;
	int _last_z = 0;

	ALLEGRO_MOUSE_STATE _mouse_state{};
	Utils::vec2 _cursor_pos;
	ALLEGRO_COLOR _color_line = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR _color_cursor = al_map_rgb(0, 0, 255);
	ALLEGRO_COLOR _color_mm_line = al_map_rgb(60, 60, 60);
	Utils::ResourceManager _resource_manager;
};

// todo: add keybinding to create multiple checkpoints at once (right mouse button?) 
// todo: add changing number of lines with scroll wheel