#include "BullCowGame.h"

BullCowGame::BullCowGame()
{
	InitWorldsList();
	InitMaxTriesMap();
}

void BullCowGame::StartGame()
{
	std::cout << "��Ϸ˵����" << std::endl;
	std::cout << "ÿһ�����ɵĵ��ʶ���û���ظ���ĸ��, ���� list, destroy" << std::endl;
	std::cout << "Bulls ��ʾ��ȷ����ĸ��������ȷ��λ��," << std::endl;
	std::cout << "Cows ��ʾ��ȷ����ĸ�����˴����λ��," << std::endl;
	std::cout << "������ȷ�ĵ����� plane, ��Ĳ�����plaen," << std::endl;
	std::cout << "��ô Bulls = 3, Cows = 2." << std::endl;

	do
	{
		std::cout << std::endl;

		//�Ӵʿ��л�ȡ����.
		std::string targetWord = GetOneWord();

		//��ʾ��ӭ����.
		Welcome(targetWord);

		//��Ϸ������.
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
	std::cout << "��ӭ����Bulls And Cows, һ����Ȥ�Ĳµ�����Ϸ!" << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "���ܲµ���� " << targetWord.length() << " ����ĸ���ĵ�����?" << std::endl;
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
				std::cout << "��ϲ�������!" << std::endl;
				break;
			}
		}
		else if (wordState == WordState::TOOLONG)
		{
			std::cout << "������ַ���̫����, ��������һ�°�!" << std::endl << std::endl;
			currentTry--;
			i--;
		}
		else
		{
			std::cout << "������ַ���̫����, ��������һ�°�!" << std::endl << std::endl;
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
	std::cout << "��������� " << currentTry << " : ";

	std::string str;
	std::cin >> str;
	return str;
}

bool BullCowGame::AskPlayAgain()
{
	std::cout << "�Ƿ�����һ����Ϸ�� y/n" << std::endl;

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
	currentTry++;						//�ۼӲµĴ���.
	ResetBullAndCow();					//����.

	//���� bull �� cow ������.
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
		//������ĸ������ȷ��λ��, ��Ϸ��ʤ.
		currentState = GameState::WIN;
	}
	else
	{
		//ƥ��ʧ��, �������ʲ�һ��.
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
