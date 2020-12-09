#pragma once

#include "AABB.h"
class CSimpleSprite;


class Runner
{
public:
	Runner();
	~Runner();

	enum Direction
	{
		DOWN,
		UP,
		LEFT,
		RIGHT,
		STOP,
	};
	void Update(float deltaTime);
	void Render();
	void DebugRender();
	void StartEndGame();
	void GetCenterPos(float& x, float& y);
	const AABB& GetAABB() const { return m_box; };
	Direction m_direction;
	void SetPreviousPosition();
	float deplacement;

private:
	
	CSimpleSprite* m_sprite;
	bool m_isPlayingEndGame;
	bool m_debugRenderOn;
	bool m_isRunning;
	AABB m_box;
	float exPosX, exPosY;


	void UpdateAABB();
};

