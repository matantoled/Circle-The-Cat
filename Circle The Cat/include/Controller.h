#pragma once
#include "Board.h"

class Controller {

public:
	Controller();
	virtual ~Controller() = default;

	Controller(const Controller&) = default;
	Controller& operator=(const Controller&) = default;
	Controller(Controller&&) = default;
	Controller& operator=(Controller&&) = default;

	void runGame();
	void setText();

private:
	void printWinLevel();
	void printWinGame();
	void draw();
	void handleLoseLevel();

	Board m_board;
	sf::RenderWindow m_window;
	sf::Text m_levelText, m_tapsText, m_loseText;
	
};