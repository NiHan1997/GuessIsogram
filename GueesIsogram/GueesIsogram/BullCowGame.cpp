#include "BullCowGame.h"

BullCowGame::BullCowGame()
{
	InitWorldsList();
	InitMaxTriesMap();
}

void BullCowGame::StartGame()
{
	std::cout << "游戏说明：" << std::endl;
	std::cout << "每一个生成的单词都是没有重复字母的, 比如 list, destroy" << std::endl;
	std::cout << "Bulls 表示正确的字母放在了正确的位置," << std::endl;
	std::cout << "Cows 表示正确的字母放在了错误的位置," << std::endl;
	std::cout << "比如正确的单词是 plane, 你的猜想是plaen," << std::endl;
	std::cout << "那么 Bulls = 3, Cows = 2." << std::endl;

	do
	{
		std::cout << std::endl;

		//从词库中获取单词.
		std::string targetWord = GetOneWord();

		//显示欢迎界面.
		Welcome(targetWord);

		//游戏进行中.
		PlayGame(targetWord);
	} while (AskPlayAgain());
}

void BullCowGame::InitWorldsList()
{
	wordsList.push_back("aim");
	wordsList.push_back("age");
	wordsList.push_back("boy");
	wordsList.push_back("you");
	wordsList.push_back("gun");

	wordsList.push_back("list");
	wordsList.push_back("game");
	wordsList.push_back("text");
	wordsList.push_back("stop");
	wordsList.push_back("play");

	wordsList.push_back("unity");
	wordsList.push_back("begin");
	wordsList.push_back("pivot");
	wordsList.push_back("audio");

	wordsList.push_back("unreal");
	wordsList.push_back("active");
	wordsList.push_back("cloudy");

	wordsList.push_back("english");
	wordsList.push_back("destory");
	wordsList.push_back("disable");
}

void BullCowGame::InitMaxTriesMap()
{
	wordLengthToMaxTries[3] = 4;
	wordLengthToMaxTries[4] = 7;
	wordLengthToMaxTries[5] = 10;
	wordLengthToMaxTries[6] = 16;
	wordLengthToMaxTries[7] = 25;
}

void BullCowGame::Welcome(std::string targetWord)
{
	std::cout << "欢迎来到Bulls And Cows, 一个有趣的猜单词游戏!" << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "你能猜到这个 " << targetWord.length() << " 个字母长的单词吗?" << std::endl;
}

void BullCowGame::PlayGame(std::string targetWord)
{
	for (int i = 1; i <= GetWorldMaxTries(targetWord); i++)
	{
		currentTryWord = GetGuess(i);
		WordState wordState = CheckWordValidity(currentTryWord, targetWord);
		if (wordState == WordState::VALID)
		{
			SubmitGuess(targetWord);
			PrintSumary();

			if (currentState == GameState::WIN)
			{
				std::cout << "恭喜你猜中了!" << std::endl;
				break;
			}
		}
		else if (wordState == WordState::TOOLONG)
		{
			std::cout << "输入的字符串太长了, 请重新输一下吧!" << std::endl << std::endl;
			currentTry--;
			i--;
		}
		else
		{
			std::cout << "输入的字符串太短了, 请重新输一下吧!" << std::endl << std::endl;
			currentTry--;
			i--;
		}
	}
}

std::string BullCowGame::GetOneWord() const
{
	srand(static_cast<unsigned>(time(0)));
	return wordsList[static_cast<int>(rand() % (wordsList.size() - 1))];
}

std::string BullCowGame::GetGuess(int currentTry)
{
	std::cout << "请输入猜想 " << currentTry << " : ";

	std::string str;
	std::cin >> str;
	return str;
}

bool BullCowGame::AskPlayAgain()
{
	std::cout << "是否再来一次游戏？ y/n" << std::endl;

	std::string str;
	std::cin >> str;

	return str == "y" || str == "Y";
}

int BullCowGame::GetWorldMaxTries(std::string targetWorld)
{
	return wordLengthToMaxTries[static_cast<int>(targetWorld.length())];
}

void BullCowGame::SubmitGuess(std::string targetWord)
{
	currentTry++;						//累加猜的次数.
	ResetBullAndCow();					//重置.

	//计算 bull 和 cow 的数量.
	for (int i = 0; i < static_cast<int>(targetWord.length()); i++)
	{
		for (int j = 0; j < static_cast<int>(targetWord.length()); j++)
		{
			if (currentTryWord[j] == targetWord[i])
			{
				if (i == j)
					bullCount++;
				else
					cowCount++;
			}
		}
	}

	if (bullCount == targetWord.length())
	{
		//所有字母都在正确的位置, 游戏获胜.
		currentState = GameState::WIN;
	}
	else
	{
		//匹配失败, 两个单词不一样.
		currentState = GameState::LOSE;
		if (currentTry == GetWorldMaxTries(targetWord))
		{
			currentState = GameState::END;
		}
	}
}

void BullCowGame::PrintSumary()
{
	std::cout << "Bulls : " << bullCount << ", Cows : " << cowCount << "\n";
}

void BullCowGame::ResetBullAndCow()
{
	bullCount = 0;
	cowCount = 0;
}

WordState BullCowGame::CheckWordValidity(std::string guessWord, std::string targetWord) const
{
	if (guessWord.length() < targetWord.length())
		return WordState::TOOSHORT;
	else if (guessWord.length() > targetWord.length())
		return WordState::TOOLONG;
	else
		return WordState::VALID;
}
