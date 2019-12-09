#pragma once

/// 游戏状态枚举.
enum class GameState : int
{
	WIN = 0,
	LOSE,
	END
};

/// 猜想单词的合法性.
enum class WordState : int
{
	VALID = 0,
	TOOLONG,
	TOOSHORT
};
