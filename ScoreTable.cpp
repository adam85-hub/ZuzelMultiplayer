
#include "ScoreTable.h"
#include "Consts.h"


ScoreTable::~ScoreTable(){
	for (auto c : _players) {
		delete c;
	}
}

void ScoreTable::addPlayer(Player* player) {
	if (_players.size() < number_of_players) {
		_players.push_back(player);
	}
}

void ScoreTable::updateTable()
{
    std::sort(_players.begin(), _players.end(), [](Player* a, Player* b) {

        if (a->GetLaps() != b->GetLaps()) {
            return a->GetLaps() > b->GetLaps();
        }

        return a->GetCurrentCheckpointIndex() > b->GetCurrentCheckpointIndex();
    });
}

void ScoreTable::render()
{

    for (int i = 0; i < (int)_players.size(); i++) {
        int laps = _players[i]->GetLaps();
        int cp = _players[i]->GetCurrentCheckpointIndex();

       
        ALLEGRO_COLOR pColor = _players[i]->GetColor();

        std::string stats = std::to_string(i + 1) + ". Miejsce, " +
            std::to_string(laps) + " okr¹¿eñ";


        Utils::draw_polish_text(
            _font_score_table,
            pColor,                
            c_RENDER_WIDTH / 4,
            300 + (i * 80),
            0,
            stats.c_str()
        );
    }


}
