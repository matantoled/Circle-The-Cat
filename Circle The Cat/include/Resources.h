#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

const int FPS = 60;
const int BOARD_SIZE = 11;
const int BOARD_EDGE = 10;
const int RADIUS = 35;
const int NUM_OF_NEIGHBORS = 6;
const int NUM_OF_LEVELS = 3;
const int FIRST_LEVEL = 1;
const int EASY_LEVEL = 14, MEDIUM_LEVEL = 9, HARD_LEVEL = 4;
const int MIDDLE_BOARD = 5;
const int NUM_OF_TEXTURES = 3;
const int NUM_OF_SOUNDS = 4;
const int SIZE_OF_TEXT = 80;
const float CIRCLE_SIZE = 80.f;
const sf::Vector2f OFFSET = { 40,0 };
const float TO_THE_MIDDLE_X = 420;
const float TO_THE_MIDDLE_Y = 70;
const sf::Color BACKGROUND_COLOR = { 55, 55, 55, 255 };
const sf::Vector2f LEVEL_NUM_TEXT_POS = { 1750.f, 650.f }, TAPS_NUM_TEXT_POS = { 1700.f, 350.f };
const sf::Vector2f LEVEL_TEXT_POS = { 1450.f, 650.f }, TAPS_TEXT_POS = { 1450.f, 350.f }, LOSE_TEXT_POS = { 480.f, 480.f };
const sf::Vector2i CAT_START_POSITION = { 5,5 };
const sf::Vector2i DEFAULT_PARENT = { 0,0 };
const float FREEZE_SEC = 3.5f;
const sf::Color TEXT_COLOR = sf::Color::Cyan;

enum class Textures
{
	cat,
	winLevel,
	winGame
};

enum class SoundType 
{
	winLevelSound,
	loseLevelSound,
	winGameSound,
	clickSound
};

enum MusicType {
	GameMusic
};

class Resources {

public:
	static Resources& instance() {
		static auto resources = Resources(); // static in function!
		return resources;
	}
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;
	const sf::Texture& getTexture(const Textures texture);
	const sf::Font& getFont();
	void playSound(const SoundType type);
	void playMusic(const MusicType type);

private:
	Resources();
	std::vector<sf::Texture> m_textures;	//to store all game textures
	sf::Font m_font;
	std::vector<sf::SoundBuffer> m_buffers;	//to store game sounds
	sf::Sound m_sound;						//to play current sound
	sf::Music m_gameMusic;					//to store game music
};
