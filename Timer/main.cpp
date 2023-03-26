#include <SFML/Graphics.hpp>
#include "timeLine.h"
#include "button.h"
#include "music.h"

sf::RenderWindow window(sf::VideoMode(300, 500), "Timer");
sf::Event event;

int main()
{
	
	timeLine seconds("fonts/Opel Sans Bold.ttf", 209, 200);
	timeLine minutes("fonts/Opel Sans Bold.ttf", 115, 200);
	timeLine hours("fonts/Opel Sans Bold.ttf", 22, 200);

	button playButton("images/play.png", 60, 60, 120, 400);
	button pauseButton("images/pause.png", 60, 60, 195, 400);
	button stopButton("images/stop.png", 60, 60, 45, 400);

	music endMusic("music/melody.ogg");

	// Text to print it at the end when the time is gone
	timeLine endText("fonts/Opel Sans Bold.ttf", 30, 100);
	endText.setTextAndSize("Time is over!", 40);
	
	sf::Clock clock;
	sf::Int32  time = 0;
	sf::Int32 pausedTimeInMilliseconds = 0;
	// pausedTimeInMilliseconds needed to remember the time passed after the latest click on pause
	// this difference is used when we start timer after pause again to show and change seconds correctly

	// set of different sets of needed buttons
	enum { timerIsStopped, timerIsPaused, timerIsCounting, timerIsOutOfTime} stateTimer;
	stateTimer = timerIsStopped;
	
	
	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			// Blocks timeLines of seconds, minutes and hours when the timer is counting or paused
			if (stateTimer == timerIsStopped)
			{
				seconds.checkForMouseWheelSpinning();
				minutes.checkForMouseWheelSpinning();
				hours.checkForMouseWheelSpinning();
			}
		}

		// Main Handler of clicks on the buttons
		if (playButton.isClicked() && (stateTimer == timerIsStopped || stateTimer == timerIsPaused) )
		{
			if (hours.getCnt() == 0 && minutes.getCnt() == 0 && seconds.getCnt() == 0)
			{ stateTimer == timerIsStopped; }
			else
			{
				sf::sleep(sf::milliseconds(100));
				stateTimer = timerIsCounting;
				time = clock.getElapsedTime().asMilliseconds() - pausedTimeInMilliseconds;
			}
		}
		else if (pauseButton.isClicked() && stateTimer == timerIsCounting)
		{
			sf::sleep(sf::milliseconds(100));
			stateTimer = timerIsPaused;
			pausedTimeInMilliseconds = clock.getElapsedTime().asMilliseconds() - time;
		}
		else if (stopButton.isClicked() && ( stateTimer == timerIsCounting || stateTimer == timerIsPaused || stateTimer == timerIsOutOfTime) )
		{
			seconds.setCntToZero();
			minutes.setCntToZero();
			hours.setCntToZero();
			stateTimer = timerIsStopped;
			pausedTimeInMilliseconds = 0;

			if (endMusic.checkMusicIsPlaying()) endMusic.stop();
		}
		
		// Counter that allows to switch seconds using Clock object to check passing every second
		// Also it executes all logic of switchin hours, minutes and seconds
		if (stateTimer == timerIsCounting && (clock.getElapsedTime().asMilliseconds() - time > 1000) )
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
				stateTimer = timerIsOutOfTime;
				endMusic.play();
			}

		}

		// This part manages different sets of buttons at different timer states
		window.clear();

		switch (stateTimer)
		{
			case timerIsStopped:
				playButton.setPosition(120, 400);
				playButton.show();
				break;
			case timerIsCounting:
				stopButton.setPosition(45, 400);
				stopButton.show();
				pauseButton.show();
				break;
			case timerIsPaused:
				playButton.setPosition(195, 400);
				stopButton.setPosition(45, 400);
				playButton.show();
				stopButton.show();
				break;
			case timerIsOutOfTime:
				stopButton.setPosition(120, 400);
				stopButton.show();
				endText.Show();
				break;
		}

		seconds.Show();
		minutes.Show();
		hours.Show();
		window.display();

	}
	return 0;
}


