#include "CellTypeConverter.h"
#include <vector>

CellTypeConverter::CellTypeConverter(void)
{
	current_cell_pointer=NULL;
}

void CellTypeConverter::Convert()
{
	if(current_cell_pointer!=NULL)
	{
		std::vector< function <void()> >::iterator the_iterator=vectorOfConvertations.begin();
		for (int i=vectorOfConvertations.size()-1;i>= 0;i--)
		{
			vectorOfConvertations[i]();
			cell_pointers.pop_back();
		}
		
		vectorOfConvertations.clear();
		cell_pointers.clear();
	}
}