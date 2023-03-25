#pragma once
#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

// This file allows to show buttons and check when they're clicked

extern sf::RenderWindow window;
extern sf::Event event;

class button
{
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	button(sf::String picturePath, int _width, int _height, int posX, int posY)
	{
		// Loading a picture of the button
		image.loadFromFile(picturePath);
		image.createMaskFromColor(sf::Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, _width, _height));
		sprite.setPosition(posX, posY);
	}

	// Allows to check if the mouse on the button object at the window
	bool isMouseOnButon()
	{
		if (sf::Mouse::getPosition(window).x > sprite.getPosition().x && sf::Mouse::getPosition(window).x < sprite.getPosition().x + 60 &&
			sf::Mouse::getPosition(window).y > sprite.getPosition().y && sf::Mouse::getPosition(window).y < sprite.getPosition().y + 60)
			return true;
		else
			return false;
	}

	// Allows to check if the object is clicked
	bool isClicked()
	{
		if (isMouseOnButon() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true;
		}
		else
			return false;
	}

	// Changes position of the button
	void setPosition(float newPosX, float newPosY)
	{
		sprite.setPosition(newPosX, newPosY);
	}

	void show()
	{
		window.draw(sprite);
	}
};
