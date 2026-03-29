#pragma once
#include "allegro5/allegro5.h"
#include "vec2.h"

#include <vector>
#include <allegro5/allegro_primitives.h>
#include <filesystem>
#include <fstream>

class CreateColliderScene {
protected:
	CreateColliderScene() {
		al_show_mouse_cursor(al_get_current_display());
	}

	void Update(KeyStatesTable key_states) {
		al_get_mouse_state(&_mouse_state);

		if ((_mouse_state.buttons & ALLEGRO_MOUSE_BUTTON_LEFT) and (_polygon_collider.size() == 0 or
			_polygon_collider[_polygon_collider.size() - 1].Distance(_mouse_state.x, _mouse_state.y) > _polygon_circle_radius * 3)) {
			_polygon_collider.emplace_back(_mouse_state.x, _mouse_state.y);
		}

		if ((key_states[ALLEGRO_KEY_BACKSPACE] & c_KEY_PRESSED) and _polygon_collider.size() > 0) {
			_polygon_collider.pop_back();
		}
	}

	void Render() {
		if (_polygon_collider.size() > 0)
			al_draw_filled_circle(_polygon_collider[0].x, _polygon_collider[0].y, _polygon_circle_radius, _color_line);

		for (int i = 1; i < _polygon_collider.size(); i++) {
			al_draw_filled_circle(_polygon_collider[i].x, _polygon_collider[i].y, _polygon_circle_radius, _color_line);
			al_draw_line(_polygon_collider[i - 1].x, _polygon_collider[i - 1].y, _polygon_collider[i].x, _polygon_collider[i].y,
				_color_line, 1);
		}

		if (_polygon_collider.size() > 2)
			al_draw_line(_polygon_collider[0].x, _polygon_collider[0].y,
				_polygon_collider.back().x, _polygon_collider.back().y, _color_line, 1);
	}

	void save_to_file(std::filesystem::path filename, std::vector<Utils::vec2>* collider_to_save = nullptr) {
		if (collider_to_save == nullptr)
			collider_to_save = &_polygon_collider;

		std::ofstream output_file;
		output_file.open(filename, std::ios::out | std::ios::trunc);
		if (!output_file.is_open())
			throw std::runtime_error("Couldnt open file: " + filename.string());

		for (Utils::vec2 point : *collider_to_save) {
			output_file << point.x << " " << point.y << ",";
		}

		output_file.close();
	}

	Utils::vec2 _cursor_position;
	std::vector<Utils::vec2> _polygon_collider;
	int _polygon_circle_radius = 4;

	ALLEGRO_MOUSE_STATE _mouse_state{};
	ALLEGRO_COLOR _color_line = al_map_rgb(255, 255, 255);
	Utils::ResourceManager _resource_manager;
};