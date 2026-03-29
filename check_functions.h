#pragma once
#include <stdexcept>
#include <string>

namespace Utils {
	// funkcja sprawdza czy zasób item_to_check zosta³ utworzony
	template <typename T>
	static void check_created(T item_to_check, std::string item_name) {
		if (!item_to_check) {
			throw std::runtime_error(item_name + " was not created successfully!");
		}
	}
	
	// funkcja s³u¿y do sprawdzania sukcesu inicjalizacji modu³ów biblioteki allegro
	static void check_initialized(bool test, std::string item_name) {
		if (!test) {
			throw std::runtime_error(item_name + " was not initialized successfully!");
		}
	}

	template <typename T>
	static void check_resource_loaded(T* resource, std::string resource_name) {
		if (resource == nullptr)
			throw std::runtime_error("Resource " + resource_name + " was not loaded succesfully!");
	}
}

