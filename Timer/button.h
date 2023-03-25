#pragma once
#pragma warning(disable : 4996)


#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

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
		if (!image.loadFromFile(picturePath))
		{
			std::cout << "No picture found\n";
			return;
		}

		image.createMaskFromColor(sf::Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, _width, _height));
		sprite.setPosition(posX, posY);
	}

	bool isMouseOnButon()
	{
		if (sf::Mouse::getPosition(window).x > sprite.getPosition().x && sf::Mouse::getPosition(window).x < sprite.getPosition().x + 60 &&
			sf::Mouse::getPosition(window).y > sprite.getPosition().y && sf::Mouse::getPosition(window).y < sprite.getPosition().y + 60)
			return true;
		else
			return false;
	}

	bool isClicked()
	{
		if (isMouseOnButon() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true;
		}
		else
			return false;
	}

	sf::Vector2f getSpritePosAsVector()
	{
		return sprite.getPosition();
	}

	void show( sf::Vector2f vector)
	{
		sprite.setPosition(vector);
		window.draw(sprite);
	}
};
