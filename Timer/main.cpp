#include <SFML/Graphics.hpp>
#include "timeLine.h"

#pragma warning(disable : 4996)

sf::RenderWindow window(sf::VideoMode(300, 500), "Timer");
sf::Event event;




int main()
{
	
	timeLine seconds("Opel Sans Bold.ttf", 22, 200);
	timeLine minutes("Opel Sans Bold.ttf", 115, 200);
	timeLine hours("Opel Sans Bold.ttf", 209, 200);

	sf::Clock clock;
	int time = 0;
	
	
	while (window.isOpen())
	{


		while (window.pollEvent(event))
		{
			seconds.checkForMouseWheelSpinning();
			if (event.type == sf::Event::Closed)
				window.close();
			
			seconds.checkForMouseWheelSpinning();
			minutes.checkForMouseWheelSpinning();
			hours.checkForMouseWheelSpinning();
		}

	

		std::cout << seconds.isMouseOnText() << " " << minutes.isMouseOnText() << " " << hours.isMouseOnText() << "\n";
		//std::cout << seconds.getTextPos().x << " " << seconds.getTextPos().y << "\n";
		//std::cout << sf::Mouse::getPosition(window).x << "\n";



		if (clock.getElapsedTime().asSeconds() - time > 1)
		{
			time = clock.getElapsedTime().asSeconds();
			//seconds.increment();
		}

		window.clear();
		seconds.Show();
		minutes.Show();
		hours.Show();
		window.display();
	}
	return 0;
}


