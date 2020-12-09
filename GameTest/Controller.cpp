#include "stdafx.h"
#include "Controller.h"

#include "app.h"

Controller::Controller():
	m_isPlayingEndGame(false)
{
//------------------------------------------------------------------------
// Cursor direction settings and management
//------------------------------------------------------------------------
	m_sprite = App::CreateSprite(".\\TestData\\cursor.bmp");
	m_sprite->SetPosition(50.0f, 100.0f);
	m_debugRenderOn = false;
	
	m_sprite->SetScale(1.0f);
}

Controller::~Controller()
{
	delete m_sprite;
}

void Controller::Update(float deltaTime)
{
	if (m_isPlayingEndGame)
	{
		return;
	}

	const float SPEED = .20f;

	float deplacement = SPEED * deltaTime;
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		x += deplacement;
		m_sprite->SetPosition(x, y);
	}
	else if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		
		x -= deplacement;
		m_sprite->SetPosition(x, y);
		
	}
	else if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		y += deplacement;
		m_sprite->SetPosition(x, y);
	}
	else if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		y -= deplacement;
		m_sprite->SetPosition(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		m_debugRenderOn = !m_debugRenderOn;
	}
	UpdateAABB();
}

void Controller::UpdateAABB()
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

void Controller::DebugRender()
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

void Controller::Render()
{
	m_sprite->Draw();
	if (m_debugRenderOn)
		DebugRender();
}

void Controller::StartEndGame()
{
	m_isPlayingEndGame = true;
}

void Controller::GetCenterPos(float& x, float& y)
{
	m_sprite->GetPosition(x, y);
}
