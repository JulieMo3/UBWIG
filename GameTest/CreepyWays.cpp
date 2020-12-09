//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app.h"
#include "Controller.h"
#include "Runner.h"
#include "Asset.h"
#include "AABB.h"
#include "MapPublisher.h"
#include "LaserWall.h"
#include "MapItem.h"
#include <vector>

//------------------------------------------------------------------------
// Set data
//------------------------------------------------------------------------

Controller* m_ctr = nullptr;
Right* m_right = nullptr;
Left* m_left = nullptr;
Up* m_up = nullptr;
Down* m_down = nullptr;
MapPublisher* m_map = nullptr;
Runner* m_player = nullptr;
bool m_isFinish = false;
int posX, posY;
CSimpleSprite* m_fontL;
CSimpleSprite* m_fontR;
CSimpleSprite* m_lose;
std::vector<LaserWall> wallList;
std::vector<Asset*> assetList;
std::vector<Asset*> newAsset;
std::vector<MapItem*> mapList;


enum GameState
{
	RUNNING,
	WIN,
	LOST
} ;

GameState globalState = RUNNING;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	m_map = new MapPublisher();
	m_ctr = new Controller();
	m_player = new Runner();
	m_player->m_direction= m_player->STOP;
	m_left = new Left(915,460);
	m_right = new Right(915,570);
	m_up = new Up(915, 232);
	m_down = new Down(915, 350);
	assetList.push_back(m_left);
	assetList.push_back(m_right);
	assetList.push_back(m_up);
	assetList.push_back(m_down);
	LaserWall wall1 = LaserWall(140, 740, 60, 60);
	LaserWall wall2 = LaserWall(140, 740, 740, 740);
	LaserWall wall3 = LaserWall(740, 740, 60, 740);
	LaserWall wall4 = LaserWall(140, 140, 60, 740);
	wallList.push_back(wall1);
	wallList.push_back(wall2);
	wallList.push_back(wall3);
	wallList.push_back(wall4);
	m_fontL = App::CreateSprite(".\\TestData\\fontL.bmp");
	m_fontR = App::CreateSprite(".\\TestData\\fontR.bmp");
	m_lose = App::CreateSprite(".\\TestData\\lose.bmp");
	m_fontL->SetPosition(430.0f, 400.0f);
	m_fontR->SetPosition(660.0f, 400.0f);
	m_lose->SetPosition(400.0f, 400.0f);
	m_player->m_direction = m_player->STOP;
	App::StartSound(".\\TestData\\font.wav");
}

void StartEndGame()
{
	
	
	m_ctr->StartEndGame();
	m_player->StartEndGame();
	
	m_left->StartEndGame();
	m_right->StartEndGame();
	m_up->StartEndGame();
	m_down->StartEndGame();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	m_ctr->Update(deltaTime);
	m_player->Update(deltaTime);
	m_left->Update(deltaTime);
	m_right->Update(deltaTime);
	m_up->Update(deltaTime);
	m_down->Update(deltaTime);
	
//------------------------------------------------------------------------
// Reload game
//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true)) {
		globalState = RUNNING;
		App::StopSound(".\\TestData\\lose.wav");
		App::StopSound(".\\TestData\\win.wav");
		Init();
	}


//------------------------------------------------------------------------
	if (globalState == RUNNING)
	{
		float xCursorPos = 0.f;
		float yCursorPos = 0.f;
		//------------------------------------------------------------------------
		// Checking if its possible to select the object to move it or drop it and do so
		//------------------------------------------------------------------------
		for (auto asset : assetList)
		{
			if (areColliding(m_ctr->GetAABB(), asset->GetAABB()) && (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))) {
				
				App::StartSound(".\\TestData\\select.wav");
				if (asset->m_pin == false)
				{
					asset->m_pin = true;
				}
				else if (asset->m_pin == true)
				{
					asset->m_pin = false;
				}
				
			}
		}
//------------------------------------------------------------------------
// Cheking collison from runner to change direction
//------------------------------------------------------------------------
		for (auto asset : assetList)
		{
			if(areColliding(m_player->GetAABB(), asset->GetAABB())) {
				
				switch (asset->m_type)
				{
				case asset->GO_RIGHT:
					m_player->m_direction = m_player->RIGHT;
					break;
				case asset->GO_LEFT:
					m_player->m_direction = m_player->LEFT;
					break;
				case asset->GO_UP:
					m_player->m_direction = m_player->UP;
					break;
				case asset->GO_DOWN:
					m_player->m_direction = m_player->DOWN;
					break;
				default:
					break;
				}
			}
		}

//------------------------------------------------------------------------
// Secure size map
//------------------------------------------------------------------------
		for (auto wall : wallList)
		{
			if (areColliding(m_player->GetAABB(), wall.GetAABB()))
			{
				StartEndGame();
				globalState = LOST;
			}
		}
//------------------------------------------------------------------------
// Map Implementation Items
//------------------------------------------------------------------------
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 8; j++) {
				MapItem* asset = new MapItem(m_map->tableau2D[i][j]);
				posX = 185 + i * 85;
				posY = 100 + j * 85;
				asset->Position(posX, posY);
				mapList.push_back(asset);
				
			}
		}
//------------------------------------------------------------------------
// Collision between wall and runner
//------------------------------------------------------------------------
		for (auto map : mapList)
		{
			if (map->m_type == 1) {
				if (areColliding(m_player->GetAABB(), map->GetAABB())) {
					StartEndGame();
					globalState = LOST;
				}
			}
			if (map->m_type == 2) {
				if (areColliding(m_player->GetAABB(), map->GetAABB())) {
					StartEndGame();
					globalState = WIN;
				}
			}
			
		}
	}
}

//------------------------------------------------------------------------
// Visual upload
//------------------------------------------------------------------------
void Render()
{

	m_fontR->Draw();
	m_fontL->Draw();
	
	for (auto map : mapList)
	{
		map->Render();
	}
	
	m_right->Render();
	m_left->Render();
	m_down->Render();
	m_up->Render();
	m_player->Render();
	m_ctr->Render();
	
	App::Print(20, 730, "X reinitialize");
	App::Print(20, 710, "Y stop move");
	App::Print(20, 690, "A select/drop");
	App::Print(20, 670, "B start move");
	for (auto wall : wallList)
	{
		wall.Render();
	}

	if (globalState == WIN)
	{
		App::StopSound(".\\TestData\\font.wav");
		App::StartSound(".\\TestData\\win.wav");
		App::Print(500, 400, "!!! WIN !!!");
		
		
	}
	if (globalState == LOST)
	{
		m_lose->Draw();
		App::StopSound(".\\TestData\\font.wav");
		//App::StartSound(".\\TestData\\lose.wav");
		App::Print(500, 400, "!!! LOST !!!");
		
	}
}
//------------------------------------------------------------------------
// End
//------------------------------------------------------------------------
void Shutdown()
{	
	delete m_ctr;
	wallList.clear();
	assetList.clear();
}
