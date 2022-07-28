#pragma once
#include "Resources.h"

class Tile {

public:
	Tile(const sf::Vector2i location);
	virtual ~Tile() = default;

	Tile(const Tile&) = default;
	Tile& operator=(const Tile&) = default;
	Tile(Tile&&) = default;
	Tile& operator=(Tile&&) = default;

	void removeAdj(const sf::Vector2i location);
	void setColor(const sf::Color color);
	void clearAdjs();
	void setParent(const sf::Vector2i parent);

	const bool checkIfEmptyTile(const sf::Vector2f& currLocation, const sf::Vector2f& catLoc);
	const sf::CircleShape& getCircle() const;
	const bool checkIfBlack() const;
	const std::vector<sf::Vector2i> getAdjList() const;
	const sf::Vector2i getParent() const;

private:
	void addAdjIfValid(const sf::Vector2i location);
	void buildAdjList(const sf::Vector2i location);

	sf::CircleShape m_circle;
	sf::Vector2i m_circleLocation;
	std::vector<sf::Vector2i> m_adjList;
	sf::Vector2i m_parent = DEFAULT_PARENT;

};