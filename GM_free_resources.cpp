#include "GameManager.h"

void GameManager::free_resources() {
	al_destroy_display(_display);
	al_destroy_timer(_timer);
	al_destroy_event_queue(_event_queue);
}