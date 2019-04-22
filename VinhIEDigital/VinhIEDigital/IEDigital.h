#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include "pch.h"

#pragma once
#ifndef IEDIGITAL
#define IEDIGITAL

const int c_minX = 0;
const int c_minY = 0;
const int c_maxX = 4;
const int c_maxY = 4;
const std::vector<std::string> DirSt{ "NORTH", "WEST", "SOUTH", "EAST" };
const std::vector<std::string> TurnSt{ "LEFT","RIGHT" };
enum Direction {
	NORTH,
	WEST,
	SOUTH,
	EAST,
	MAX_DIR
};
enum Turn {
	LEFT,
	RIGHT,
	MAX_TURN
};
class Pacman {
private:
	int m_x{ 0 };
	int m_y{ 0 };
	int m_dir{ NORTH };
	bool start{ false };
public:
	bool init(int x, int y, int dir);
	bool ready();
	void move();
	void turn(int cmd);
	void report();
};
void upperSt(std::string &data);
size_t splitSt(const std::string &txt, std::vector<std::string> &strs, char ch);
void pacmanGame();
#endif // !IEDIGITAL
