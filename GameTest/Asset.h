#pragma once

#include "AABB.h"
class CSimpleSprite;


class Asset
{
public:
	Asset();
	~Asset();

	void Update(float deltaTime);
	void Render();
	void DebugRender();
	void setPreviousPosition(int x, int y);
	void StartEndGame();

	void GetCenterPos(float& x, float& y);
	const AABB& GetAABB() const { return m_box; };
	bool IsInside(float xPos, float yPos);
	bool m_pin;
	enum Type
	{
		GO_UP,
		GO_DOWN,
		GO_LEFT,
		GO_RIGHT,
	};
	Type m_type;
	CSimpleSprite* m_sprite;
	bool m_isPlayingEndGame;
	bool m_debugRenderOn;
	AABB m_box;


	void UpdateAABB();
};

class Left : public Asset 
{
public:
	Left(float x, float y);
	~Left();
	
};

class Right : public Asset
{
public:
	Right(float x, float y);
	~Right();

};

class Up : public Asset
{
public:
	Up(float x, float y);
	~Up();

};

class Down : public Asset
{
public:
	Down(float x, float y);
	~Down();

};


