#pragma once
#include "Board.h"
#include <iostream>

Board::Board()
{
	setText();
}
//=========================================================
void Board::setLevel(const int level)
{
	m_winLevel = false;
	m_loseLevel = false;
	m_isValidPath = true;
	m_catOnTheEdge = false;
	m_level = level;
	m_tapsCounter = 0;			// reset the taps
	m_cat.setLocetaion(CAT_START_POSITION);
	m_board.clear();
	m_board.resize(BOARD_SIZE);

	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			Tile tile({ x,y });
			m_board[y].push_back(tile);
		}
	}
	setRandomBlackCircles();
}
//=========================================================
void Board::setText() 
{
	//set font
	m_numOfLevelText.setFont(Resources::instance().getFont());
	m_numOftapsText.setFont(Resources::instance().getFont());

	//set text size
	m_numOfLevelText.setCharacterSize(SIZE_OF_TEXT);
	m_numOftapsText.setCharacterSize(SIZE_OF_TEXT);

	//set text color
	m_numOfLevelText.setFillColor(sf::Color::Cyan);
	m_numOftapsText.setFillColor(sf::Color::Cyan);

	//set text position
	m_numOfLevelText.setPosition(LEVEL_NUM_TEXT_POS);
	m_numOftapsText.setPosition(TAPS_NUM_TEXT_POS);
}
//=========================================================
const bool Board::checkIfTapOnEmptyTile(const sf::Vector2f& currLocation)
{
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			if (m_board[y][x].checkIfEmptyTile(currLocation, m_cat.getCatLoc())) {
				m_tapsCounter++;
				updateAdjList({ x,y });
				return true;
			}
		}
	}
	return false;
}
//=========================================================
void Board::updateAdjList(const sf::Vector2i location) 
{
	// Note: the cast to long long is to disable warning 26451

	if (location.y - 1 >= 0)
		m_board[long long(location.y) - 1][location.x].removeAdj(location);						// up
	if (location.y + 1 < BOARD_SIZE)
		m_board[long long(location.y) + 1][location.x].removeAdj(location);						// down
	if (location.x - 1 >= 0)
		m_board[location.y][long long(location.x) - 1].removeAdj(location);						// left
	if (location.x + 1 < BOARD_SIZE)
		m_board[location.y][long long(location.x) + 1].removeAdj(location);						// right

	if (location.y % 2 == 0) {
		if (location.x - 1 >= 0 && location.y - 1 >= 0)
			m_board[long long(location.y) - 1][long long(location.x) - 1].removeAdj(location);	// left up
		if (location.y + 1 < BOARD_SIZE && location.x - 1 >= 0)
			m_board[long long(location.y) + 1][long long(location.x) - 1].removeAdj(location);	// left down
	}
	else {
		if (location.y - 1 >= 0 && location.x + 1 < BOARD_SIZE)
			m_board[long long(location.y) - 1][long long(location.x) + 1].removeAdj(location);	// right up
		if (location.x + 1 < BOARD_SIZE && location.y + 1 < BOARD_SIZE)
			m_board[long long(location.y) + 1][long long(location.x) + 1].removeAdj(location);	// right down
	}
	m_board[location.y][location.x].clearAdjs();
}
//=========================================================
void Board::setRandomBlackCircles()
{
	int num_of_circles, x, y;
	srand(static_cast<unsigned>(time(nullptr)));

	// init how many random black circles we do
	if (m_level == 1)
		num_of_circles = EASY_LEVEL;
	else if (m_level == 2)
		num_of_circles = MEDIUM_LEVEL;
	else
		num_of_circles = HARD_LEVEL;

	for (int i = 0; i < num_of_circles; i++) {
		do {
			x = rand() % BOARD_SIZE;
			y = rand() % BOARD_SIZE;
		} while (m_board[y][x].checkIfBlack());
		if (x == MIDDLE_BOARD && y == MIDDLE_BOARD) {	// cat position
			i--;
			continue;
		}
		m_board[y][x].setColor(sf::Color::Black);
		updateAdjList({ x, y });
	}
}
//=========================================================
// This function use the BFS algorithm to move the cat.
void Board::moveCat()
{
	if (m_catOnTheEdge) {		// check if the cat is one step from win
		m_loseLevel = true;
		return;
	}
	if (m_isValidPath) {	// if there are at least one free path to the edge - search

		bool visited[BOARD_SIZE][BOARD_SIZE] = { {false} }; // Mark all the vertices as not visited
		std::list<sf::Vector2i> queue;						// Create a queue for BFS
		sf::Vector2i start = m_cat.getCatBoardLoc();		// set the start position of the cat

		// Mark the current node as visited and enqueue it
		visited[m_cat.getCatBoardLoc().y][m_cat.getCatBoardLoc().x] = true;
		queue.push_back(start);

		while (!queue.empty()) {

			// Dequeue a vertex from queue
			start = queue.front();
			queue.pop_front();

			// Get all adjacent vertices
			for (auto adjecent : m_board[start.y][start.x].getAdjList())
			{
				if (!visited[adjecent.y][adjecent.x])
				{
					// If a adjacent has not been visited, then mark it visited and enqueue it
					visited[adjecent.y][adjecent.x] = true;
					// set the parent of the Tile to find the path at the end
					m_board[adjecent.y][adjecent.x].setParent(start);
					queue.push_back(adjecent);
					// check if the adjecent is on some edge. if so, move the cat to his new location
					if (adjecent.y == 0 || adjecent.y == BOARD_EDGE || adjecent.x == 0 || adjecent.x == BOARD_EDGE) {
						FindTheNewCatLocation(adjecent, m_cat.getCatBoardLoc());
						return;
					}
				}
			}
		}
		if (checkIfWinLevel())	// check if the player win this level
			return;

		m_isValidPath = false;	// if we got here, that means that there are no free path to some edge
		moveToRandomLocation();
	}
	else {						// there are no free path to some edge so we dont need to check again
		if (checkIfWinLevel())
			return;
		moveToRandomLocation();
	}
}
//=========================================================
void Board::FindTheNewCatLocation(sf::Vector2i newLoc, const sf::Vector2i catCurrLoc) {

	while (true) {		// move forward until we get to the parent of the cat location  
		if (catCurrLoc == m_board[newLoc.y][newLoc.x].getParent())
			break;
		newLoc = m_board[newLoc.y][newLoc.x].getParent();
	}
	m_cat.setLocetaion(newLoc);

	if (newLoc.y == 0 || newLoc.y == BOARD_EDGE || newLoc.x == 0 || newLoc.x == BOARD_EDGE)
		m_catOnTheEdge = true;
	
}
//=========================================================
const bool Board::checkIfWinLevel() 
{
	sf::Vector2i start = m_cat.getCatBoardLoc();
	if (m_board[start.y][start.x].getAdjList().size() == 0) {
		m_winLevel = true;
		return true;
	}
	return false;
}
//=========================================================
void Board::moveToRandomLocation() 
{
	sf::Vector2i start = m_cat.getCatBoardLoc();
	size_t size = m_board[start.y][start.x].getAdjList().size();
	if (size > 0)
		m_cat.setLocetaion(m_board[start.y][start.x].getAdjList()[rand() % size]);
}
//=========================================================
const sf::Sprite Board::getCatSprite() const 
{
	return m_cat.getSprite();
}
//=========================================================
const sf::Text Board::getNumOfLevelText()
{
	m_numOfLevelText.setString(std::to_string(m_level));
	return m_numOfLevelText;
}
//=========================================================
const sf::Text Board::getNumOfTapsText()
{
	m_numOftapsText.setString(std::to_string(m_tapsCounter));
	return m_numOftapsText;
}
//=========================================================
const sf::CircleShape& Board::getCircle(const int y, const int x)
{
	return m_board[y][x].getCircle();
}
//=========================================================
const unsigned Board::getTaps() const
{
	return m_tapsCounter;
}
//=========================================================
const bool Board::getWinLevel() const
{
	return m_winLevel;
}
//=========================================================
const bool Board::getLoseLevel() const
{
	return m_loseLevel;
}
//=========================================================