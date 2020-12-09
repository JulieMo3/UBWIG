
#include "stdafx.h"
#include "MapPublisher.h"
#include "MapItem.h"
#include "app.h"


MapPublisher::MapPublisher()
{
//------------------------------------------------------------------------
// Map setting wall and ground plan
//------------------------------------------------------------------------
	MapItem* m_map_set;
	int posX, posY;
//------------------------------------------------------------------------
// Cleaar visual of map (bette then in a loop)
//Each change of 0 and 1 and 2 will change the visual aspect of map and his physic will follow
//Easy way to modify quickly the map
//------------------------------------------------------------------------
	int tabVisu[7][8] = { 1,1,1,1,1,1,1,1,     
						1,0,0,0,0,0,0,1,
						1,0,0,0,0,0,0,1, 
						1,0,0,1,1,1,0,1, 
						2,0,0,0,0,1,0,1, 
						1,0,0,0,0,1,0,1, 
						1,1,1,1,1,1,1,1, };

	for (int i = 0; i < 7; i++)
		tableau2D[i] = nullptr;
	for (int i = 0; i < 7; i++)
		tableau2D[i] = new int[8];
	for (int i = 0; i < 7; i++) {
		
			for (int j = 0; j < 8; j++) {
				tableau2D[i][j] = tabVisu[i][j];
			}
	}
	
	
	


};

MapPublisher::~MapPublisher()
{
	
}









