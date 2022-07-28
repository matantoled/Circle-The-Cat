#pragma once
#include "Resources.h"

class Cat {

public:
	Cat();
	virtual ~Cat() = default;

	Cat(const Cat&) = default;
	Cat& operator=(const Cat&) = default;
	Cat(Cat&&) = default;
	Cat& operator=(Cat&&) = default;

	const sf::Sprite getSprite() const;
	const sf::Vector2f getCatLoc() const;
	const sf::Vector2i getCatBoardLoc() const;
	void setLocetaion(const sf::Vector2i loc);

private:
	sf::Sprite m_sprite;
	sf::Vector2i m_boardLoc;

};