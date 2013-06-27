#include "CellConnectionTeleport.h"


CellConnectionTeleport::CellConnectionTeleport(void)
{
}


CellConnectionTeleport::~CellConnectionTeleport(void)
{
}
std::pair<int,int> CellConnectionTeleport::returnCellToTeleport(Cell* currentCell)
{
	for (auto it=cells.begin();it!=cells.end();it++)
		if (it->first==currentCell){
			if (++it!=cells.end()) return std::pair<int,int>(it->second.first,it->second.second);
			else return std::pair<int,int>(cells.begin()->second.first,cells.begin()->second.second);
		}
	
}