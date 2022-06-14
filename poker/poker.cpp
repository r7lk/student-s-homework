/*-------------------------------------------------------------------------
 *
 * poker.cpp
 * 		自动发扑克牌 52张牌无大小王随机发给4个
 *
 * loaction
 * 		src/poker.cpp
 *
 *-------------------------------------------------------------------------
 */

#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef enum Poker_color
{
	T_spade = 0,
	T_plum_blossom,
	T_red_heart,
	T_rhomb
}Poker_color;

typedef size_t Number;

#define POKER_SINGLE_NUMBER		13
#define PLAYER_TOTAL_NUMBER		4

static string Poker_color_name[] = 
	{
		//"??", "?? ", "?? ", "?",
		"黑桃", "梅花", "红心", "方砖"
	};

static string Poker_number[] = 
	{
		"A", "2", "3", "4",
		"5", "6", "7", "8", "9",
		"10", "J", "Q", "K",
	};

class Poker
{
public:
	void display()
	{
		cout << Poker_color_name[m_color] 
			<< setw(2 )<< Poker_number[m_number-1] << " ";
	}
	Poker_color 	m_color;
	Number			m_number;
};

typedef vector<Poker>	Pokers;

static string Player_name[] = 
	{
		"一号玩家", "二号玩家", "三号玩家", "四号玩家"
	};

class Player
{
public:
	Player() {};
	~Player() {};

	void set_number(Number _number) {m_player_number = _number;}
	void init() {m_pokers.clear();}
	void push(Poker _poker) {m_pokers.push_back(_poker);}

	void display()
	{
		cout << Player_name[m_player_number-1] << " ";
		for(int i=0; i<POKER_SINGLE_NUMBER; i++)
			m_pokers[i].display();
		cout << endl;
	}

private:
	Player(const Player& _player) = delete;

private:
	Pokers			m_pokers;
	Number			m_player_number;
};

class GameTable
{
public:
	GameTable(int _count):m_count(_count)
	{
		m_players[0].set_number(1);
		m_players[1].set_number(2);
		m_players[2].set_number(3);
		m_players[3].set_number(4);

		m_pokers.clear();
	}
	
	~GameTable()
	{
		m_pokers.clear();;
	}

	void init()
	{
		for(int i=1; i<=POKER_SINGLE_NUMBER; i++)
		{
			Poker poker;
			poker.m_number = i;
			poker.m_color = T_spade; 
			m_pokers.push_back(poker);
			poker.m_color = T_plum_blossom;
			m_pokers.push_back(poker);
			poker.m_color = T_red_heart;
			m_pokers.push_back(poker);
			poker.m_color = T_rhomb;
			m_pokers.push_back(poker);
		}
	}

	void play()
	{
		for(size_t j=0; j<m_count; j++)
		{
			for (int i=0; i<PLAYER_TOTAL_NUMBER; i++)
				m_players[i].init();

			cout << j+1 << "轮" << endl;
			srand(time(0));
			random_shuffle(m_pokers.begin(), m_pokers.end());
			for(int i=0; i<POKER_SINGLE_NUMBER; i++)
			{
				m_players[0].push(m_pokers[0+i]);
				m_players[1].push(m_pokers[POKER_SINGLE_NUMBER+i]);
				m_players[2].push(m_pokers[POKER_SINGLE_NUMBER*2+i]);
				m_players[3].push(m_pokers[POKER_SINGLE_NUMBER*3+i]);
			}
			display();
			cout << endl;
		}
	}

private:
	GameTable(const GameTable& _game_table) = delete;
	
	void display()
	{
		for(size_t i=0; i<PLAYER_TOTAL_NUMBER; i++)
			m_players[i].display();
	}

private:
	Player			m_players[PLAYER_TOTAL_NUMBER];
	Pokers			m_pokers;
	Number			m_count;
};

int
main(int argc, char* argv[])
{
	int count = 0;
	if (argc > 1)
		count = atoi(argv[1]);
	else
		cin >> count;
	assert(0 < count);

	GameTable* game_table = new GameTable(count);
	assert(NULL != game_table);

	game_table->init();
	game_table->play();

	delete game_table;
	game_table = NULL;
	return 0;
}
