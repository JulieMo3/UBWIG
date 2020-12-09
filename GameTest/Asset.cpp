#include "stdafx.h"
#include "Asset.h"

#include "app.h"

//------------------------------------------------------------------------
// Arrow direction settings and management
//------------------------------------------------------------------------
Asset::Asset() :
	m_isPlayingEndGame(false)
{
	
	m_sprite = App::CreateSprite(".\\TestData\\gauche.bmp");
	m_sprite->SetPosition(500.0f, 100.0f);
	m_debugRenderOn = false;
	m_pin = false;

	m_sprite->SetScale(1.0f);
}

Asset::~Asset()
{
	delete m_sprite;
}

void Asset::Update(float deltaTime)
{
	if (m_isPlayingEndGame)
	{
		return;
	}
//------------------------------------------------------------------------
// If selected get same movement as cursor like pined effect
//------------------------------------------------------------------------
	const float SPEED = .20f;

	float deplacement = SPEED * deltaTime;
	if (m_pin == true) {
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
	}
	
	UpdateAABB();
}

void Asset::UpdateAABB()
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

void Asset::setPreviousPosition(int x, int y) {
	m_sprite->SetPosition(x, y);
}

void Asset::DebugRender()
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

void Asset::Render()
{
	m_sprite->Draw();
	if (m_debugRenderOn)
		DebugRender();
}

bool Asset::IsInside(float xPos, float yPos)
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

void Asset::StartEndGame()
{
	m_isPlayingEndGame = true;
}

void Asset::GetCenterPos(float& x, float& y)
{
	m_sprite->GetPosition(x, y);
}

Left::Left(float x, float y) {
	m_sprite = App::CreateSprite(".\\TestData\\gauche.bmp");
	m_sprite->SetPosition(x, y);
	m_sprite->SetScale(1.0f);
	m_type = GO_LEFT;
}

Left::~Left() {

}
//------------------------------------------------------------------------
// Classe fille 
//------------------------------------------------------------------------
Right::Right(float x, float y) {
	m_sprite = App::CreateSprite(".\\TestData\\droite.bmp");
	m_sprite->SetPosition(x, y);
	m_sprite->SetScale(1.0f);
	m_type = GO_RIGHT;
}

Right::~Right() {

}

Up::Up(float x, float y) {
	m_sprite = App::CreateSprite(".\\TestData\\haut.bmp");
	m_sprite->SetPosition(x, y);
	m_sprite->SetScale(1.0f);
	m_type = GO_UP;
}

Up::~Up() {

}


Down::Down(float x, float y) {
	m_sprite = App::CreateSprite(".\\TestData\\bas.bmp");
	m_sprite->SetPosition(x, y);
	m_sprite->SetScale(1.0f);
	m_type = GO_DOWN;
}

Down::~Down() {

}
