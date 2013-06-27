#pragma once
#include "Cell.h"
#include <functional> 
#include <vector>

using namespace std;
using std::tr1::function;

class CellEmpty;
class Cell;
class CellTypeConverter
{
private:
	std::vector<Cell**> cell_pointers;
	std::vector< function <void()> > vectorOfConvertations;
public:
	CellTypeConverter(void);
	template <class new_type> void CreateConvert(int x,int y)
	{
		cell_pointers.push_back(&global_map[x][y]);
		function <void()> Convertation=[&]()
		{
			int temp1=0,temp2=0,temp3=0,temp4=0;
			temp1=(*cell_pointers.back())->GetX();
			temp2=(*cell_pointers.back())->GetY();
			temp3=(*cell_pointers.back())->GetH();
			temp4=(*cell_pointers.back())->GetW();

			delete *cell_pointers.back();
			*cell_pointers.back()=new new_type;
			(**cell_pointers.back()).SetDestination(temp1,temp2,temp3,temp4);
		};
		vectorOfConvertations.push_back(Convertation);
	}
	void Convert();
};

