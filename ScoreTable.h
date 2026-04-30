#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <allegro5/allegro_font.h>
#include "draw_polish_text.h"

#include "Player.h"


class ScoreTable
{
public:
    
    ScoreTable(int count, ALLEGRO_FONT* font)
        : number_of_players(count), _font_score_table(font) {
    }

    ~ScoreTable();

    void updateTable();
    void render();

    void addPlayer(Player* player);
    void setFont(ALLEGRO_FONT* font) {
        _font_score_table = font;
	}

private:
    int number_of_players;
    std::vector<Player*> _players;
    ALLEGRO_FONT* _font_score_table;
};