#pragma once
struct CellStruct
{
	int CellX;
	int CellY;
public: 
	CellStruct()
	{
		CellX=0;
		CellY=0;
	}
	CellStruct(int x,int y)
	{
		CellX=x;
		CellY=y;
	}
};