#pragma once

/// ��Ϸ״̬ö��.
enum class GameState : int
{
	WIN = 0,
	LOSE,
	END
};

/// ���뵥�ʵĺϷ���.
enum class WordState : int
{
	VALID = 0,
	TOOLONG,
	TOOSHORT
};
