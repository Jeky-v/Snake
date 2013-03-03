#include "CellTypeConverter.h"


CellTypeConverter::CellTypeConverter(void)
{
	current_cell_pointer=NULL;
}

void CellTypeConverter::Convert()
{
	if(current_cell_pointer!=NULL)
	{
		Convertation();
	}
}