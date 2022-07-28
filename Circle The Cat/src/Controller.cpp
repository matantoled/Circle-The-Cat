#pragma once
#include "Controller.h"

Controller::Controller() : m_window(sf::VideoMode(1920, 1080), "Circle The Cat") {
	
	m_window.setFramerateLimit(FPS);
	setText();
}
//=========================================================
void Controller::setText()
{
	//set font
	m_levelText.setFont(Resources::instance().getFont());
	m_tapsText.setFont(Resources::instance().getFont());
	m_loseText.setFont(Resources::instance().getFont());

	//set text size
	m_levelText.setCharacterSize(SIZE_OF_TEXT);
	m_tapsText.setCharacterSize(SIZE_OF_TEXT);
	m_loseText.setCharacterSize(SIZE_OF_TEXT);

	//set text color
	m_levelText.setFillColor(sf::Color::Cyan);
	m_tapsText.setFillColor(sf::Color::Cyan);
	m_loseText.setFillColor(sf::Color::Cyan);
	m_loseText.setStyle(sf::Text::Bold);

	//set text position
	m_levelText.setPosition(LEVEL_TEXT_POS);
	m_tapsText.setPosition(TAPS_TEXT_POS);
	m_loseText.setPosition(LOSE_TEXT_POS);

	//set text
	m_levelText.setString("LEVEL: ");
	m_tapsText.setString("TAPS: ");
	m_loseText.setString("YOU LOSE! TRY AGAIN!");
}
//=========================================================
void Controller::runGame()
{
	Resources::instance().playMusic(MusicType::GameMusic);
	
	// main loop. run all levels
	for (int level = 1; level <= NUM_OF_LEVELS;) {
		m_board.setLevel(level);
		while (m_window.isOpen())
		{
			draw();
			if (auto event = sf::Event{}; m_window.waitEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed: {
					m_window.close();
					exit(EXIT_SUCCESS);
					break; }

				case sf::Event::MouseButtonReleased: {
					auto clickLocation = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

					switch (event.mouseButton.button)
					{
					case sf::Mouse::Button::Left: {	// the player click on left button mouse:
						if (m_board.checkIfTapOnEmptyTile(clickLocation)) {	// if press on empty tile, then:
							m_board.moveCat();
							Resources::instance().playSound(SoundType::clickSound);
						}
						break; }
					}
					break; }
				}
			}
			// if win level -> print and level++
			if (m_board.getWinLevel()) {
				if (level + 1 <= NUM_OF_LEVELS)
					printWinLevel();
				level++;
				break;
			}
			// if lose level -> play lose sound and print message
			else if (m_board.getLoseLevel()) {
				handleLoseLevel();
				break;
			}
		}
	}
	printWinGame();
}
//=========================================================
void Controller::draw() 
{
	m_window.clear(BACKGROUND_COLOR);
	
	// draw the Tiles
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			m_window.draw(m_board.getCircle(y,x));
		}
	}

	m_window.draw(m_board.getCatSprite());		// draw the cat
	m_window.draw(m_levelText);					// draw the LEVEL
	m_window.draw(m_tapsText);					// draw the TAPS
	m_window.draw(m_board.getNumOfTapsText());	// draw the numbers of taps
	m_window.draw(m_board.getNumOfLevelText());	// draw the level number

	m_window.display();
}
//=========================================================
void Controller::printWinLevel() {

	m_window.clear();

	sf::Sprite winSprite(Resources::instance().getTexture(Textures::winLevel));
	m_window.draw(winSprite);
	Resources::instance().playSound(SoundType::winLevelSound);
	m_window.display();
	while (true) //wating for user press enter to continue
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			break;
}
//=========================================================
void Controller::handleLoseLevel() {

	const sf::Time freezeLength{ sf::seconds(FREEZE_SEC) };	// for lose message
	sf::Clock freezeClock;								// for lose message
	Resources::instance().playSound(SoundType::loseLevelSound);	// sound
	m_window.draw(m_loseText);	// draw "you lose"
	m_window.display();
	freezeClock.restart();		// restart the clock that the message will display for 4 sec
	while (freezeClock.getElapsedTime() < freezeLength) {
		sf::Event event;
		m_window.pollEvent(event);
	}
}
//=========================================================
void Controller::printWinGame() 
{
	m_window.clear();

	sf::Sprite winSprite(Resources::instance().getTexture(Textures::winGame));
	m_window.draw(winSprite);
	Resources::instance().playSound(SoundType::winGameSound);
	m_window.display();
	while (true) //wating for user press escape to continue
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;
}
