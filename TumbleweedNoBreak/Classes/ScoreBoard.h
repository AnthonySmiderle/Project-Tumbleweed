#pragma once
#include <fstream>
#include "Player.h"
namespace Sedna
{
	static class ScoreBoard
	{
	public:
		void writeScore(Sedna::Player* player, std::string name, int loc);
		void getScore(Sedna::XinputController* controller, Sedna::Stick sticks[], float dt, Sedna::Player* player, int loc);
		bool hasWritten = false;
		std::ifstream highFileIn;
		std::ofstream highFileOut;
		float hasLetGo = 0.0f;
		cocos2d::Label *highScoreLabel;
		cocos2d::Label *highScoreNameLabel;
		float flashingScoreTimer = 0.0f;
		int scoreName[3] = { 65,65,65 };
		int currentScoreName = 0;
		cocos2d::Sprite* flashingScore1;
		cocos2d::Sprite* flashingScore2;
	private:
		

	};

}