#pragma once

#include <SFML/Audio.hpp>


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

	bool checkMusicIsPlaying()
	{
		return musicIsPlaying;
	}
};