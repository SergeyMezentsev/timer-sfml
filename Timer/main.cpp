#include <SFML/Graphics.hpp>
#include "timeLine.h"
#include "button.h"

#pragma warning(disable : 4996)

sf::RenderWindow window(sf::VideoMode(300, 500), "Timer");
sf::Event event;




int main()
{
	
	timeLine seconds("Opel Sans Bold.ttf", 209, 200);
	timeLine minutes("Opel Sans Bold.ttf", 115, 200);
	timeLine hours("Opel Sans Bold.ttf", 22, 200);

	button playButton("images/play.png", 60, 60, 120, 400);
	button pauseButton("images/pause.png", 60, 60, 195, 400);
	button stopButton("images/stop.png", 60, 60, 45, 400);



	sf::Clock clock;
	unsigned int time = 0;
	unsigned int pausedTimeInMilliseconds = 0;




	bool timerIsCounting = false;
	
	
	while (window.isOpen())
	{


		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
				window.close();
			

			if (!timerIsCounting)
			{
				seconds.checkForMouseWheelSpinning();
				minutes.checkForMouseWheelSpinning();
				hours.checkForMouseWheelSpinning();
			}
		}

	

		if (playButton.isClicked() && !timerIsCounting)
		{
			if (hours.getCnt() == 0 && minutes.getCnt() == 0 && seconds.getCnt() == 0)
			{timerIsCounting = false;}
			else
			{timerIsCounting = true;}


			clock.restart();
			time = clock.getElapsedTime().asMilliseconds() + pausedTimeInMilliseconds;
		}
		else if (pauseButton.isClicked() && timerIsCounting)
		{
			timerIsCounting = false;
			pausedTimeInMilliseconds = clock.getElapsedTime().asMilliseconds() % 1000;

		}
		else if (stopButton.isClicked() && timerIsCounting)
		{
			seconds.setCntToZero();
			minutes.setCntToZero();
			hours.setCntToZero();
			timerIsCounting = false;
		}
		
		



		if (timerIsCounting && (clock.getElapsedTime().asMilliseconds() - time > 1000) )
		{
			time = clock.getElapsedTime().asMilliseconds();
			seconds.decrement();
			if (seconds.getCnt() == 59)
			{
				minutes.decrement();
			}
			if (minutes.getCnt() == 59 && seconds.getCnt() == 59)
			{
				hours.decrement();
			}
			if (hours.getCnt() == 0 && minutes.getCnt() == 0 && seconds.getCnt() == 0)
			{
				timerIsCounting = false;
			}

		}




		window.clear();

		if(timerIsCounting)
		{
			stopButton.show();
			pauseButton.show();
		}
		else
			playButton.show();

		seconds.Show();
		minutes.Show();
		hours.Show();
		window.display();
	}
	return 0;
}


