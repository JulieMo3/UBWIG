#pragma once

#include "AABB.h"
class CSimpleSprite;


class MapItem
{
public:
	MapItem(int type);
	~MapItem();

	void Render();
	void StartEndGame();
	CSimpleSprite* m_sprite;
	const AABB& GetAABB() const { return m_box; };
	bool IsInside(float xPos, float yPos);
	bool m_isPlayingEndGame;
	AABB m_box;
	void Position(int x, int y);
	void Draw();
	int m_type;
	

	
};
