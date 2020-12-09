#include "stdafx.h"
#include "MapItem.h"

#include "app.h"

MapItem::MapItem(int type) :
	m_isPlayingEndGame(false)
//------------------------------------------------------------------------
// Map implementation item following MapPublosher plan
//------------------------------------------------------------------------
{
	if (type == 0) {
		m_sprite = App::CreateSprite(".\\TestData\\sol.bmp");
		m_type = type;
	}
	else if (type == 1) 
	{
		m_sprite = App::CreateSprite(".\\TestData\\wall.bmp");
		m_type = type;
	}
	else if (type == 2)
	{
		m_sprite = App::CreateSprite(".\\TestData\\exit.bmp");
		m_type = type;
	}
	
}

MapItem::~MapItem()
{
	delete m_sprite;
	
}

void MapItem::Position(int x, int y) {
	m_sprite->SetPosition(x, y);
	m_sprite->SetScale(1.0f);
	m_box.x1 = x - 85 * 0.5f;
	m_box.y1 = y - 85 * 0.5f;
	m_box.x2 = x + 85 * 0.5f;
	m_box.y2 = y + 85 * 0.5f;
}

void MapItem::Draw() {
	m_sprite->Draw();
}


void MapItem::Render()
{
	m_sprite->Draw();
	
}

bool MapItem::IsInside(float xPos, float yPos)
{
	if (xPos > m_box.x1 && xPos < m_box.x2)
	{
		if (yPos > m_box.y1 && yPos < m_box.y2)
		{
			return true;
		}
	}

	return false;
}

void MapItem::StartEndGame()
{
	m_isPlayingEndGame = true;
}

