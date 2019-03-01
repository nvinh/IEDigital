#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <exception>

#include "pch.h"
#include "IEDigital.h"
bool Pacman::checkInitValue(int x, int y, int dir) {
	if ((x < 0) || (x > c_maxX) ||
		(y < 0) || (y > c_maxY) ||
		(dir < 0) || (dir >= MAX_DIR)) {
		//std::cout << "Error\n";
		return false;
	}
	else {
		m_x = x;
		m_y = y;
		m_dir = dir;
		m_start = true;
		return true;
	}
}
bool Pacman::init(std::string cmd) {
	std::vector<std::string> inputCmd;
	upperSt(cmd);
	splitSt(cmd, inputCmd, ' ');
	if (inputCmd[0] == "PLACE") {
		if (inputCmd.size() >= 2) {
			//std::cout << inputCmd[1] << "\n";
			std::vector<std::string> Pos;
			splitSt(inputCmd[1], Pos, ',');
			//for (int k = 0; k < static_cast<int>(Pos.size()); ++k) {
				//std::cout << Pos[k] << "-";
			//}
			if (Pos.size() >= 3) {
				int x;
				int y;
				try {
					x = std::stoi(Pos[0]);
				}
				catch (std::exception& e) {
					//std::cout << e.what() << "\n";
					return false;
				}
				try {
					y = std::stoi(Pos[1]);
				}
				catch (std::exception& e) {
					//std::cout << e.what() << "\n";
					return false;
				}
				int dLen = static_cast<int>(DirSt.size());
				int i(0);
				bool found = false;
				int d(0);
				while (!found && i < dLen) {
					if (Pos[2] == DirSt[i]) {
						d = i;
						found = true;
					}
					++i;
				}
				if (found) return checkInitValue(x, y, d);
			}
		}
	}
	return false;
}
void Pacman::move() {
		if (!m_start) {
			std::cout << "Pacman was not correctly placed\n";
			return;
		}
		if (m_dir == NORTH) {		// NORTH,WEST, SOUTH, EAST
			++m_y;
			if (m_y > c_maxY) m_y = c_maxY;
		}
		if (m_dir == SOUTH) {
			--m_y;
			if (m_y < c_minY) m_y = c_minY;
		}
		if (m_dir == EAST) {
			++m_x;
			if (m_x > c_maxX) m_x = c_maxX;
		}
		if (m_dir == WEST) {
			--m_x;
			if (m_x < c_minX) m_x = c_minX;
		}
		std::cout << "Pacman moved. Current position [" << m_x << "," << m_y << "] toward " << DirSt[m_dir] << "\n";
	}
void Pacman::turn(int cmd) {
		if (!m_start) {
			std::cout << "Pacman was not correctly placed\n";
			return;
		}
		//std::cout << "cmd=" << cmd << "-";
		if (cmd < 0 || cmd >= MAX_TURN) {
			std::cout << "Invalid turning request.\n";
		}
		else {
			if (cmd == RIGHT) {
				--m_dir;
				if (m_dir < 0) m_dir = EAST;

			}
			if (cmd == LEFT) {
				++m_dir;
				if (m_dir >= MAX_DIR) m_dir = NORTH;
			}
			std::cout << "Turned " << TurnSt[cmd] << ". ";
			std::cout << "Current direction: " << DirSt[m_dir] << "\n";
		}
	}
void Pacman::report() {
		if (!m_start) {
			std::cout << "Pacman was not correctly placed\n";
			return;
		}
		std::cout << "Pacman position: x= " << m_x << ", y= " << m_y << ", direction= " << DirSt[m_dir] << std::endl;
	}

size_t Pacman::splitSt(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;
		pos = txt.find(ch, initialPos);
	}
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
	return strs.size();
}

void upperSt(std::string &data) {
	std::for_each(data.begin(), data.end(), [](char & c) {
		c = static_cast<char>(::toupper(c));
	});
}

void PacmanGame() {
	bool start(false);
	bool stop(false);
	Pacman pacman;
	std::cout << "Enter a command to init and run Pacman game:\n";
	while (!stop) {
		std::string cmd;
		std::getline(std::cin, cmd);
		//std::cout << "cmd= " << cmd << "\n";
		upperSt(cmd);
		if (!start) {
			start = pacman.init(cmd);
			if (!start) std::cout << "Pacman is not placed. Please place it first using command Place at somewhere within [" <<
				c_minX << "," << c_minY << "]and[" << c_maxX << "," << c_maxY << "], West, North, South, or East\n";			
		}
		if (start) {
			if (cmd.substr(0, 5) == "PLACE") pacman.init(cmd);
			if (cmd == "MOVE") pacman.move();
			if (cmd == "REPORT") pacman.report();
			if (cmd == "LEFT") pacman.turn(0);
			if (cmd == "RIGHT") pacman.turn(1);
			if (cmd == "QUIT") stop = true;
			std::cout << "Pacman is here. Now you can MOVE, LEFT, RIGHT, REPORT, or QUIT:\n";
		}
	}
}
