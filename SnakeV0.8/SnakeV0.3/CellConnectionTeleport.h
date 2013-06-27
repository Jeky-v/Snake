#pragma once
#include "cellconnection.h"
#include "Cell.h"
class CellConnectionTeleport :
	public CellConnection
{
public:
	CellConnectionTeleport(void);
	~CellConnectionTeleport(void);
    std::pair<int,int> returnCellToTeleport(Cell* currentCell);
};

