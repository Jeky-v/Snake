#pragma once
#include "Cell.h"
#include <functional> 
using namespace std;
using std::tr1::function;

class CellEmpty;
class Cell;
class CellTypeConverter
{
private:
	Cell** current_cell_pointer;
	function <void()> Convertation;
public:
	CellTypeConverter(void);
	void SetCellPointer(Cell * new_p);
	template <class new_type> void CreateConvert(int x,int y)
	{
		current_cell_pointer=&global_map[x][y];

		Convertation=[&]()
		{
			int temp1=0,temp2=0,temp3=0,temp4=0;
			temp1=(*current_cell_pointer)->GetX();
			temp2=(*current_cell_pointer)->GetY();
			temp3=(*current_cell_pointer)->GetH();
			temp4=(*current_cell_pointer)->GetW();
			delete *current_cell_pointer;
			*current_cell_pointer=new new_type;
			(**current_cell_pointer).SetDestination(temp1,temp2,temp3,temp4);
		};
	}
	void Convert();
};

