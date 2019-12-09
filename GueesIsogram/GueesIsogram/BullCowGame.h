#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <time.h>
#include "GameConst.h"

class BullCowGame
{
private:
	std::vector<std::string> wordsList;						// 单词词库表.
	std::unordered_map<int, int> wordLengthToMaxTries;		// 单词长度决定能够猜想的次数.

	std::string currentTryWord;				//当前猜的单词.

	int bullCount;							//正确的字母 在正确的地方 的字母数量.
	int cowCount;							//正确的字母 在错误的地方 的字母数量.	
	int currentTry;							// 当前猜想的次数.

	GameState currentState;					//当前游戏状态.

public:
	BullCowGame();
	BullCowGame(const BullCowGame& rhs) = delete;
	BullCowGame& operator=(const BullCowGame& rhs) = delete;
	~BullCowGame() = default;

	/// 开始游戏.
	void StartGame();

private:
	/// 初始化词库.	
	void InitWorldsList();

	/// 初始化单词长度决定猜想次数的键值对.
	void InitMaxTriesMap();

	/// 进入游戏.
	void Welcome(std::string targetWord);

	/// 游戏进行过程.
	void PlayGame(std::string targetWord);

	/// 从词库中获取一个单词.
	std::string GetOneWord() const;

	/// 获取当前猜想次数的猜想.
	std::string GetGuess(int currentTry);

	/// 询问玩家是否再来一次.
	bool AskPlayAgain();

	/// 获取单词最大的猜想次数.
	int GetWorldMaxTries(std::string targetWorld);

	/// 提交猜想.
	void SubmitGuess(std::string targetWord);

	/// 打印猜想比较后的结果提示.
	void PrintSumary();

	/// 游戏数据重置.
	void ResetBullAndCow();

	/// 检查猜想单词是否匹配.
	WordState CheckWordValidity(std::string guessWord, std::string targetWord) const;
};
