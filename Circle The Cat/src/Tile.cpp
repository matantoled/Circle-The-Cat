#pragma once
#include "Tile.h"

Tile::Tile(const sf::Vector2i location)
{
	m_circleLocation = location;

	m_circle.setFillColor(sf::Color::Yellow);
	m_circle.setRadius(RADIUS);
	m_circle.setPosition({ TO_THE_MIDDLE_X + CIRCLE_SIZE * location.x, TO_THE_MIDDLE_Y + CIRCLE_SIZE * location.y });
	if (location.y % 2 != 0)
		m_circle.move(OFFSET);

	buildAdjList(location);
}
//=========================================================
void Tile::buildAdjList(const sf::Vector2i location) 
{
	addAdjIfValid({ location.x , location.y + 1 });				// down neighbor
	addAdjIfValid({ location.x , location.y - 1 });				// up neighbor
	addAdjIfValid({ location.x + 1 , location.y });				// right neighbor
	addAdjIfValid({ location.x - 1 , location.y });				// left neighbor

	if (location.y % 2 == 0) {
		addAdjIfValid({ location.x - 1 , location.y - 1 });		// left up neighbor
		addAdjIfValid({ location.x - 1 , location.y + 1 });		// left down neighbor
	}
	else {
		addAdjIfValid({ location.x + 1 , location.y + 1 });		// right up neighbor
		addAdjIfValid({ location.x + 1 , location.y - 1 });		// right down neighbor
	}
}
//=========================================================
void Tile::removeAdj(const sf::Vector2i location) 
{
	for (int i = 0; i < m_adjList.size(); i++) {
		if (m_adjList[i] == location) {
			m_adjList.erase(m_adjList.begin() + i);
			break;
		}
	}
}
//=========================================================
const bool Tile::checkIfEmptyTile(const sf::Vector2f& currLocation, const sf::Vector2f& catLoc)
{
	if (m_circle.getFillColor() == sf::Color::Yellow &&
		m_circle.getPosition() != catLoc &&
		m_circle.getGlobalBounds().contains(currLocation)) {
		m_circle.setFillColor(sf::Color::Black);
		return true;
	}
	else
		return false;
}
//=========================================================
void Tile::addAdjIfValid(const sf::Vector2i location)
{
	if (location.x >= 0 && location.y >= 0 && location.x < BOARD_SIZE && location.y < BOARD_SIZE)
		m_adjList.push_back(location);
}
//=========================================================
const sf::CircleShape& Tile::getCircle() const
{
	return m_circle;
}
//=========================================================
const bool Tile::checkIfBlack() const
{
	return m_circle.getFillColor() == sf::Color::Black;
}
//=========================================================
void Tile::setColor(const sf::Color color)
{
	m_circle.setFillColor(color);
}
//=========================================================
void Tile::clearAdjs()
{
	m_adjList.clear();
}
//=========================================================
const std::vector<sf::Vector2i> Tile::getAdjList() const
{
	return m_adjList;
}
//=========================================================
void Tile::setParent(const sf::Vector2i parent)
{
	m_parent = parent;
}
//=========================================================
const sf::Vector2i Tile::getParent() const
{
	return m_parent;
}
//=========================================================