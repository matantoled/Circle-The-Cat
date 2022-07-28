#pragma once
#include "Cat.h"

Cat::Cat()
{
	m_sprite.setTexture(Resources::instance().getTexture(Textures::cat));
	m_sprite.setPosition({ TO_THE_MIDDLE_X + CIRCLE_SIZE * MIDDLE_BOARD, TO_THE_MIDDLE_Y + CIRCLE_SIZE * MIDDLE_BOARD });
	m_sprite.move(OFFSET);
	m_boardLoc = { MIDDLE_BOARD,MIDDLE_BOARD };
}
//=========================================================
const sf::Sprite Cat::getSprite() const
{
	return m_sprite;
}
//=========================================================
const sf::Vector2f Cat::getCatLoc() const
{
	return m_sprite.getPosition();
}
//=========================================================
const sf::Vector2i Cat::getCatBoardLoc() const
{
	return m_boardLoc;
}
//=========================================================
void Cat::setLocetaion(const sf::Vector2i loc)
{
	m_boardLoc = loc;
	m_sprite.setPosition({ TO_THE_MIDDLE_X + CIRCLE_SIZE * loc.x, TO_THE_MIDDLE_Y + CIRCLE_SIZE * loc.y });
	if (loc.y % 2 != 0)
		m_sprite.move(OFFSET);
}
//=========================================================