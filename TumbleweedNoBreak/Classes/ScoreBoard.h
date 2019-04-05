#pragma once
#include <fstream>
#include "Player.h"
namespace Sedna
{
	static class ScoreBoard
	{
	public:
		void writeScore(Sedna::Player* player, std::string name, int loc);//this is file reader writer
		void getScore(Sedna::XinputController* controller, Sedna::Stick sticks[], float dt, Sedna::Player* player, int loc);//this collects the higherscore of the player
		bool hasWritten = false;
		std::ifstream highFileIn;//file in and out
		std::ofstream highFileOut;
		cocos2d::Label *highScoreLabel;
		cocos2d::Label *highScoreNameLabel;
		float flashingScoreTimer = 0.0f;//timers so that there is a delay between moving characters
		float hasLetGo = 0.0f;
		int scoreName[3] = { 65,65,65 };//numbers that are converted to chars
		int currentScoreName = 0;
		cocos2d::Sprite* flashingScore1;//these are arrows to display what letter they are changing
		cocos2d::Sprite* flashingScore2;
	private:
		

	};

}