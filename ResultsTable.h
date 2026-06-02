#pragma once
#include "Table.h"
#include "RaceStats.h"

class ResultsTable : public Table
{
public:
	ResultsTable(RaceStats*);
	~ResultsTable() override {};

	void Render() const;
private:
	RaceStats* _race_stats;
};

