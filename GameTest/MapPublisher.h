#pragma once
#include <vector>
#include "AABB.h"
class CSimpleSprite;


class MapPublisher
{
public:
	MapPublisher();
	~MapPublisher();
	void Render();
	
	int** tableau2D = new int* [7];
	
	
private:
	int posX, posY;
};


