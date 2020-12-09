#include "stdafx.h"
#include "Runner.h"

#include "app.h"

Runner::Runner() :
	m_isPlayingEndGame(false)
{
//------------------------------------------------------------------------
// Setting and management player behavior
//------------------------------------------------------------------------
	m_sprite = App::CreateSprite(".\\TestData\\jack.bmp");
	m_sprite->SetPosition(597.0f, 615.0f);
	m_debugRenderOn = false;
	deplacement = 0;
	m_sprite->SetScale(1.0f);
}

Runner::~Runner()
{
	delete m_sprite;
}

void Runner::Update(float deltaTime)
{
	float x, y;
	if (m_isPlayingEndGame)
	{
		return;
	}

	const float SPEED = .10f;
//------------------------------------------------------------------------
// Continuous movement when B pressed
//------------------------------------------------------------------------
	
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		deplacement = SPEED * deltaTime;
		m_direction = LEFT;	
	}
	
//------------------------------------------------------------------------
// Player changing direction (changes when collision with an Asset object type )
//------------------------------------------------------------------------
	switch (m_direction)
	{
	case STOP:
		m_sprite->GetPosition(x, y);
		m_sprite->SetPosition(x, y);
		break;
	case DOWN:
		m_sprite->GetPosition(x, y);
		exPosX = x;
		exPosY = y;
		y -= deplacement;
		m_sprite->SetPosition(x, y);
		break;
	case UP:
		m_sprite->GetPosition(x, y);
		exPosX = x;
		exPosY = y;
		y += deplacement;
		m_sprite->SetPosition(x, y);
		break;
	case LEFT:
		m_sprite->GetPosition(x, y);
		exPosX = x;
		exPosY = y;
		x -= deplacement;
		m_sprite->SetPosition(x, y);
		break;
	case RIGHT:
		m_sprite->GetPosition(x, y);
		exPosX = x;
		exPosY = y;
		x += deplacement;
		m_sprite->SetPosition(x, y);
		break;
	default:
		break;
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_Y, true))
	{
		m_direction = STOP;
	}
	
	UpdateAABB();
}
//------------------------------------------------------------------------
// Debug used fonction to change position when character blocked are restart
//------------------------------------------------------------------------
void Runner::SetPreviousPosition() {
	m_sprite->SetPosition(597.0f, 615.0f);
	m_direction = STOP;
}

void Runner::UpdateAABB()
{
	float x = 0.f;
	float y = 0.f;
	float width = m_sprite->GetWidth();
	float height = m_sprite->GetHeight();
	m_sprite->GetPosition(x, y);

	m_box.x1 = x - width * 0.5f;
	m_box.y1 = y - height * 0.5f;
	m_box.x2 = x + width * 0.5f;
	m_box.y2 = y + height * 0.5f;
}

void Runner::DebugRender()
{
	float x = 0.f;
	float y = 0.f;
	m_sprite->GetPosition(x, y);
	float width = m_sprite->GetWidth();
	float height = m_sprite->GetHeight();


	float xMinPos = x - width * 0.5f;
	float yMinPos = y - height * 0.5f;
	float xMaxPos = x + width * 0.5f;
	float yMaxPos = y + height * 0.5f;


	App::DrawLine(xMinPos, yMinPos, xMaxPos, yMinPos, 1.f, 1.f, 0.f);
	App::DrawLine(xMaxPos, yMinPos, xMaxPos, yMaxPos, 1.f, 1.f, 0.f);
	App::DrawLine(xMaxPos, yMaxPos, xMinPos, yMaxPos, 1.f, 1.f, 0.f);
	App::DrawLine(xMinPos, yMaxPos, xMinPos, yMinPos, 1.f, 1.f, 0.f);
}

void Runner::Render()
{
	m_sprite->Draw();
	if (m_debugRenderOn)
		DebugRender();
}

void Runner::StartEndGame()
{
	m_isPlayingEndGame = true;
}

void Runner::GetCenterPos(float& x, float& y)
{
	m_sprite->GetPosition(x, y);
	
}
