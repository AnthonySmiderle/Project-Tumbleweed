#include "ScoreBoard.h"

void Sedna::ScoreBoard::writeScore(Sedna::Player * player, std::string name,int loc)
{
	highFileIn = std::ifstream("Saloon_Scores.txt");
	if (highFileIn.is_open())
	{
		std::string input;
		std::vector<std::string> scoreSheet;
		while (std::getline(highFileIn, input))
		{
			scoreSheet.push_back(input);
		}
		highFileIn.close();
		std::string HighestScore;
		int intHighScore = 0;

		intHighScore = player->getScore();
		HighestScore = std::to_string(intHighScore);
		scoreSheet.push_back(name + HighestScore);
		HighestScore = name + " had " + HighestScore + " Points!";

		for (unsigned int i = 0; i < scoreSheet.size(); i++)
		{
			for (unsigned int n = 0; n < scoreSheet.size() - 1; n++)
			{
				if (stoi(scoreSheet[n].substr(3)) < stoi(scoreSheet[n + 1].substr(3)))
				{
					std::string temp = scoreSheet[n];
					scoreSheet[n] = scoreSheet[n + 1];
					scoreSheet[n + 1] = temp;
				}
			}
		}
		if (scoreSheet.size() > 7)
			scoreSheet.pop_back();
		highFileOut = std::ofstream("Saloon_Scores.txt");
		if (highFileOut.is_open())
			for (unsigned int i = 0; i < scoreSheet.size(); i++)
				highFileOut << scoreSheet[i] + "\n";


		highFileOut.close();

		HighestScore = "";
		for (unsigned int i = 0; i < scoreSheet.size(); i++)
		{
			HighestScore += scoreSheet[i].substr(0, 3) + "  " + scoreSheet[i].substr(3) + "\n";
		}
		highScoreLabel->setString(HighestScore);
		highScoreLabel->setPosition(cocos2d::Vec2(230, loc));
		highScoreLabel->setVisible(true);
		highScoreNameLabel->setVisible(false);
	}
	else
	{
		highFileOut = std::ofstream("Saloon_Scores.txt");
		if (highFileOut.is_open())
		{
			highFileOut.close();
		}
		highFileOut = std::ofstream();
		writeScore(player, name,loc);
	}

	hasWritten = true;
}

void Sedna::ScoreBoard::getScore(Sedna::XinputController * controller, Sedna::Stick sticks[], float dt, Sedna::Player * player, int loc)
{
	

	flashingScoreTimer += dt;
	if (((int)(flashingScoreTimer * 2)) % 2 == 0)
	{
		flashingScore1->setVisible(false);
		flashingScore2->setVisible(false);
	}
	else
	{
		flashingScore1->setVisible(true);
		flashingScore2->setVisible(true);
	}
	if (sticks[0].y > 0.3 && !hasLetGo)
	{
		if (scoreName[currentScoreName] == 65)
		{
			scoreName[currentScoreName] = 90;
		}
		else
		{
			scoreName[currentScoreName] = scoreName[currentScoreName] - 1;
		}
		hasLetGo += dt;
	}
	if (sticks[0].y < -0.3 && !hasLetGo)
	{
		if (scoreName[currentScoreName] == 90)
		{
			scoreName[currentScoreName] = 65;
		}
		else
		{
			scoreName[currentScoreName] = scoreName[currentScoreName] + 1;
		}
		hasLetGo += dt;
	}
	if (controller->isButtonPressed(Sedna::A) && !hasLetGo)
	{
		currentScoreName++;
		hasLetGo += dt;
	}
	if (controller->isButtonPressed(Sedna::B) && !hasLetGo)
	{
		if (currentScoreName > 0)
			currentScoreName--;
		hasLetGo += dt;
	}
	if (hasLetGo > 0.3f)
		hasLetGo = 0.0f;
	if (hasLetGo)
		hasLetGo += dt;
	std::string temp;
	temp += static_cast<char>(scoreName[0]);
	temp += static_cast<char>(scoreName[1]);
	temp += static_cast<char>(scoreName[2]);
	highScoreNameLabel->setString(temp);
	if (currentScoreName == 3)
	{
		writeScore(player, temp, loc);
		currentScoreName++;
		flashingScore1->setVisible(false);
		flashingScore2->setVisible(false);
	}
}
