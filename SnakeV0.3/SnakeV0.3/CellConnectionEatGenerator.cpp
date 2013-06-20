#include "CellConnectionEatGenerator.h"
#include "CellEat.h"

CellConnectionEatGenerator::CellConnectionEatGenerator(void)
{
}


CellConnectionEatGenerator::~CellConnectionEatGenerator(void)
{
}

void CellConnectionEatGenerator::generate(Cell* currentCell)
{
	for (auto it=cells.begin();it!=cells.end();it++)
		if (it->first!=currentCell){
			Converter.CreateConvert<CellEat>(it->second.first,it->second.second);		
		}
		
}

