#pragma once
#pragma warning(disable : 4996)		// Ignore certain error

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

// This file/class is used to show numbers of hours, minutes and seconds
// Also it's used to show texts
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
		// Loading needed font and set default text: "00"
		font.loadFromFile(fontFilePath);
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

	// Allows to increase hours, minutes, seconds by 1
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

	// Allows to decrease hours, minutes, seconds by 1
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

	// cheks if the mouse is on the object
	bool isMouseOnText()
	{
		if (sf::Mouse::getPosition(window).x > text.getPosition().x && sf::Mouse::getPosition(window).x < text.getPosition().x + 70 &&
			sf::Mouse::getPosition(window).y > text.getPosition().y && sf::Mouse::getPosition(window).y < text.getPosition().y + 60)
			return true;
		else
			return false;
	}

	// Allows to easilly change numbers of hours, min, sec when the mouse is on the object
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

	void setCntToZero()
	{
		cnt = 0;
		numberText.str("");
		numberText.clear();
		numberText << 0 << 0;
		text.setString(numberText.str());
	}

	// This function needed when the object is a text
	// So it allows to set new text and size of letters
	void setTextAndSize(sf::String newText, int size)
	{
		numberText.str("");
		numberText.clear();
		numberText << (std::string)newText;
		text.setString(numberText.str());
		text.setCharacterSize(size);
	}

	void Show()
	{
		window.draw(text);
	}
};