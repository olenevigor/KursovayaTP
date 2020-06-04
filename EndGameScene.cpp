#include "EndGameScene.h"

EndGameScene::EndGameScene(int Evens, int Odds) :
	evens(Evens), odds(Odds) { }

void EndGameScene::init()
{
	font.loadFromFile("Roboto-Medium.ttf");

	winText.setFont(font);

	// Определение победителя
	if (odds > evens)
		winText.setString("Player 1 win!");
	else if (evens > odds)
		winText.setString("Player 2 win!");
	else
		winText.setString("Draw.");

	int halfWidth = window.getSize().x / 2;
	winText.setPosition(halfWidth - winText.getGlobalBounds().width / 2, 70);

	evenNumbersText.setFont(font);
	evenNumbersText.setString("Even numbers: " + std::to_string(evens));
	evenNumbersText.setPosition(halfWidth - evenNumbersText.getGlobalBounds().width / 2, 100);

	oddsNumbersText.setFont(font);
	oddsNumbersText.setString("Odd numbers: " + std::to_string(odds));
	oddsNumbersText.setPosition(halfWidth - oddsNumbersText.getGlobalBounds().width / 2, 130);

	backButton.setFont(font);
	backButton.setText("Return to menu");
	backButton.setPosition(halfWidth - backButton.getSize().x / 2, 180);
}

void EndGameScene::update()
{
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			SceneManager::getInstance().quit();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			SceneManager::getInstance().closeScene();
		}

		backButton.input(event, window);
		if (backButton.getState() == state::clicked)
		{
			SceneManager::getInstance().closeScene();
		}
	}
}

void EndGameScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	window.draw(winText);
	window.draw(evenNumbersText);
	window.draw(oddsNumbersText);
	backButton.render(window);

	window.display();
}