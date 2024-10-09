#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>
#include <sstream>

namespace ApplesGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init game resources (terminate if error)
		assert(data.playerTexture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.ObstacleTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
		assert(data.EatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(data.GameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));
		assert(data.ClickButtonSoundBuffer.loadFromFile(RESOURCES_PATH + "ClickButton.wav"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.AppleEat.setBuffer(data.EatAppleSoundBuffer);
		data.GameOver.setBuffer(data.GameOverSoundBuffer);
		data.ClickButton.setBuffer(data.ClickButtonSoundBuffer);

		// Init player
		InitPlayer(data.player, data.playerTexture);

		// Init apples
		data.apples.clear();
		ClearApplesGrid(data.applesGrid);
		int numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
		data.apples.resize(numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, data.appleTexture);
			ResetAppleState(apple);
			AddAppleToGrid(data.applesGrid, apple);
		}

		// Init Obstacles
		data.Obstacles.clear();
		ClearObstacleGrid(data.ObstacleGrid);
		int NumObstacle = MIN_OBSTACLES + rand() % (MAX_OBSTACLES + 1 - MIN_OBSTACLES);
		data.Obstacles.resize(NumObstacle);
		for (Obstacle& Obstacle : data.Obstacles)
		{
			InitObstacle(Obstacle, data.ObstacleTexture);
			ResetObstacleState(Obstacle);
			AddObstacleToGrid(data.ObstacleGrid, Obstacle);
		}


		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to pause");
		data.inputHintText.setOrigin(GetItemOrigin(data.inputHintText, { 1.f, 0.f }));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			data.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			data.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			data.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			data.player.direction = PlayerDirection::Left;
		}

		// Update player
		UpdatePlayer(data.player, timeDelta);

		ApplesSet collidingApples;
		if (FindPlayerCollisionWithApples(data.player.position, data.applesGrid, collidingApples))
		{
			for (Apple* apple : collidingApples)
			{
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples)
				{
					// Move apple to a new random position
					ResetAppleState(*apple);
					AddAppleToGrid(data.applesGrid, *apple);
					data.AppleEat.play();
				}
				else
				{
					// Mark apple as eaten
					MarkAppleAsEaten(*apple);
					RemoveAppleFromGrid(data.applesGrid, *apple);
					data.AppleEat.play();
				}

				// Increase eaten apples counter
				data.numEatenApples++;

				// Increase player speed
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration)
				{
					data.player.speed += ACCELERATION;
				}
			}
		}

		ObstacleSet collidingObstacles;
		if (FindPlayerCollisionWithObstacle(data.player.position, data.ObstacleGrid, collidingObstacles))
		{
			for (Obstacle* Obstacle : collidingObstacles)
			{
				// Find player in records table and update his score
				game.recordsTable[PLAYER_NAME] = std::max(game.recordsTable[PLAYER_NAME], data.numEatenApples);
				data.GameOver.play();
				PushGameState(game, GameStateType::GameOver, false);
			}
		}

		bool isGameFinished = (data.numEatenApples == data.apples.size())
			&& !((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples);
		// Check collision with screen border
		if (isGameFinished || HasPlayerCollisionWithScreenBorder(data.player))
		{
			// Find player in records table and update his score
			game.recordsTable[PLAYER_NAME] = std::max(game.recordsTable[PLAYER_NAME], data.numEatenApples);
			data.GameOver.play();
			PushGameState(game, GameStateType::GameOver, false);
		}

		data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(data.player, window);
		// Draw apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}

		for (Obstacle& Obstacle : data.Obstacles)
		{
			DrawObstacle(Obstacle, window);
		}

		data.scoreText.setOrigin(GetItemOrigin(data.scoreText, { 0.f, 0.f }));
		data.scoreText.setPosition(10.f, 10.f);
		window.draw(data.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);
	}
}
