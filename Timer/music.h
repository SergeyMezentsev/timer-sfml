#pragma once
#include <SFML/Audio.hpp>

// This file allows to connect new music easilly using class

class music
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
	bool musicIsPlaying;

public:
	music(sf::String musicFilePath)
	{
		buffer.loadFromFile(musicFilePath);
		sound.setBuffer(buffer);
		sound.setLoop(true);
		musicIsPlaying = false;
	}

	void play()
	{
		sound.play();
		musicIsPlaying = true;
	}

	void stop()
	{
		sound.stop();
		musicIsPlaying = false;
	}

	// This function needed to check if the music is playing in the main function
	bool checkMusicIsPlaying()
	{
		return musicIsPlaying;
	}
};