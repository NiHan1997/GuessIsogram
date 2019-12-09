#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <time.h>
#include "GameConst.h"

class BullCowGame
{
private:
	std::vector<std::string> wordsList;						// ���ʴʿ��.
	std::unordered_map<int, int> wordLengthToMaxTries;		// ���ʳ��Ⱦ����ܹ�����Ĵ���.

	std::string currentTryWord;				//��ǰ�µĵ���.

	int bullCount;							//��ȷ����ĸ ����ȷ�ĵط� ����ĸ����.
	int cowCount;							//��ȷ����ĸ �ڴ���ĵط� ����ĸ����.	
	int currentTry;							// ��ǰ����Ĵ���.

	GameState currentState;					//��ǰ��Ϸ״̬.

public:
	BullCowGame();
	BullCowGame(const BullCowGame& rhs) = delete;
	BullCowGame& operator=(const BullCowGame& rhs) = delete;
	~BullCowGame() = default;

	/// ��ʼ��Ϸ.
	void StartGame();

private:
	/// ��ʼ���ʿ�.	
	void InitWorldsList();

	/// ��ʼ�����ʳ��Ⱦ�����������ļ�ֵ��.
	void InitMaxTriesMap();

	/// ������Ϸ.
	void Welcome(std::string targetWord);

	/// ��Ϸ���й���.
	void PlayGame(std::string targetWord);

	/// �Ӵʿ��л�ȡһ������.
	std::string GetOneWord() const;

	/// ��ȡ��ǰ��������Ĳ���.
	std::string GetGuess(int currentTry);

	/// ѯ������Ƿ�����һ��.
	bool AskPlayAgain();

	/// ��ȡ�������Ĳ������.
	int GetWorldMaxTries(std::string targetWorld);

	/// �ύ����.
	void SubmitGuess(std::string targetWord);

	/// ��ӡ����ȽϺ�Ľ����ʾ.
	void PrintSumary();

	/// ��Ϸ��������.
	void ResetBullAndCow();

	/// �����뵥���Ƿ�ƥ��.
	WordState CheckWordValidity(std::string guessWord, std::string targetWord) const;
};
