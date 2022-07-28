#pragma once
#include "Resources.h"

Resources::Resources() 
{
	m_font.loadFromFile("Panipuri.ttf");
	m_textures.resize(NUM_OF_TEXTURES);
	m_buffers.resize(NUM_OF_SOUNDS);

	m_textures[int(Textures::cat)].loadFromFile("cat.png");
	m_textures[int(Textures::winLevel)].loadFromFile("nextLevel.png");
	m_textures[int(Textures::winGame)].loadFromFile("winGame.png");

	m_gameMusic.openFromFile("backMusic.ogg");
	m_buffers[int(SoundType::winLevelSound)].loadFromFile("win2.wav");
	m_buffers[int(SoundType::loseLevelSound)].loadFromFile("lose.wav");
	m_buffers[int(SoundType::winGameSound)].loadFromFile("win.ogg");
	m_buffers[int(SoundType::clickSound)].loadFromFile("click.wav");
}
//=========================================================
const sf::Texture& Resources::getTexture(const Textures texture)
{
	switch (texture)
	{
	case Textures::cat:
		return m_textures[int(Textures::cat)];
	case Textures::winLevel:
		return m_textures[int(Textures::winLevel)];
	case Textures::winGame:
		return m_textures[int(Textures::winGame)];
	}
	throw std::runtime_error("No Texture of that type");
}
//=========================================================
const sf::Font& Resources::getFont()
{
	return m_font;
}
//=========================================================
void Resources::playSound(const SoundType type)
{
	switch (type)
	{
		// sounds
	case SoundType::winLevelSound:
		m_sound.setBuffer(m_buffers[int(SoundType::winLevelSound)]);
		break;
	case SoundType::loseLevelSound:
		m_sound.setBuffer(m_buffers[int(SoundType::loseLevelSound)]);
		break;
	case SoundType::winGameSound:
		m_gameMusic.stop();
		m_sound.setBuffer(m_buffers[int(SoundType::winGameSound)]);
		break;
	case SoundType::clickSound:
		m_sound.setBuffer(m_buffers[int(SoundType::clickSound)]);
		break;
	}
	m_sound.play();
}
//=========================================================
void Resources::playMusic(const MusicType type) {

	if (type == GameMusic) {
		m_gameMusic.play();
		m_gameMusic.setLoop(true);
	}
}