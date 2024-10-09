#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Apple.h"
#include "Obstacle.h"
#include "Player.h"


namespace ApplesGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture ObstacleTexture;
		sf::SoundBuffer EatAppleSoundBuffer;
		sf::SoundBuffer GameOverSoundBuffer;
		sf::SoundBuffer ClickButtonSoundBuffer;
		sf::Font font;
		sf::Sound AppleEat;
		sf::Sound GameOver;
		sf::Sound ClickButton;

		// Game data
		Player player;
		std::vector<Apple> apples;
		ApplesGrid applesGrid;
		int numEatenApples = 0;

		std::vector<Obstacle> Obstacles;
		ObstacleGrid ObstacleGrid;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}
