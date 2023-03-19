#pragma once
#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

extern sf::RenderWindow window;
extern sf::Event event;


class timeLine
{
	sf::Font font;
	sf::Text text;
	int cnt;
	std::ostringstream numberText;

public:
	timeLine(sf::String fontFilePath, int posX, int posY)
	{
		if (!font.loadFromFile(fontFilePath))
		{
			std::cout << "No fonts found\n";
			return;
		}

		text.setFont(font);
		text.setCharacterSize(60);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::White);
		text.setPosition(posX, posY);

		numberText.str("");
		numberText.clear();
		numberText << (cnt - cnt%10)/10 << cnt%10;
		text.setString(numberText.str());
	}

	void increment()
	{
		if (cnt >= 59)
			cnt = 0;
		else
			cnt++;
		numberText.str("");
		numberText.clear();
		numberText << (cnt - cnt % 10) / 10 << cnt%10;
		text.setString(numberText.str());
	}

	void decrement()
	{
		if (cnt <= 0)
			cnt = 59;
		else
			cnt--;
		numberText.str("");
		numberText.clear();
		numberText << (cnt - cnt % 10) / 10 << cnt%10;
		text.setString(numberText.str());
	}

	bool isMouseOnText()
	{
		if (sf::Mouse::getPosition(window).x > text.getPosition().x && sf::Mouse::getPosition(window).x < text.getPosition().x + 70 &&
			sf::Mouse::getPosition(window).y > text.getPosition().y && sf::Mouse::getPosition(window).y < text.getPosition().y + 60)
			return true;
		else
			return false;
	}

	void checkForMouseWheelSpinning()
	{
		if (event.type == sf::Event::MouseWheelMoved && isMouseOnText())
		{
			if (event.mouseWheel.delta == 1)
				increment();
			else if (event.mouseWheel.delta == -1)
				decrement();
		}
	}

	int getCnt()
	{
		return cnt;
	}

	void Show()
	{
		window.draw(text);
	}
};