#pragma once
#include "Resources.h"
#include "Tile.h"
#include "Cat.h"
#include <list>

class Board {

public:
	Board();
	virtual ~Board() = default;

	Board(const Board&) = default;
	Board& operator=(const Board&) = default;
	Board(Board&&) = default;
	Board& operator=(Board&&) = default;

	void setLevel(const int level);
	void moveCat();
	
	const sf::Text getNumOfTapsText();
	const sf::Text getNumOfLevelText();
	const unsigned getTaps() const;
	const bool checkIfTapOnEmptyTile(const sf::Vector2f& currLocation);
	const sf::CircleShape& getCircle(const int y, const int x);
	const sf::Sprite getCatSprite() const;
	const bool checkIfWinLevel();
	const bool getWinLevel() const;
	const bool getLoseLevel() const;

private:
	void moveToRandomLocation();
	void FindTheNewCatLocation(sf::Vector2i newLoc, const sf::Vector2i catCurrLoc);
	void updateAdjList(const sf::Vector2i location);
	void setRandomBlackCircles();
	void setText();

	Cat m_cat;
	std::vector<std::vector<Tile>> m_board;		// the board
	bool m_winLevel = false;
	bool m_loseLevel = false;
	bool m_isValidPath = true;					// to check if need to do BFS
	bool m_catOnTheEdge = false;				// to check if the is on the edge of the board
	unsigned m_tapsCounter = 0;					// count the taps of player
	int m_level = 1;
	sf::Text m_numOfLevelText;					// to print text of level number 
	sf::Text m_numOftapsText;					// to print text of how many taps
};