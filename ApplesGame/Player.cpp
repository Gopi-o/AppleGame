#include "Player.h"
#include <assert.h>
#include "Constans.h"
#include "Apple.h"


namespace ApplesGame
{
	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		// Init player state
		player.position.x = (float)SCREEN_WIDTH / 2.f;
		player.position.y = (float)SCREEN_HEGHT / 2.f;
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Up;

		// Init sprite
		player.sprite.setTexture(texture);
		player.sprite.setOrigin(GetItemOrigin(player.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		player.sprite.setScale(GetSpriteScale(player.sprite, { PLAYER_SIZE, PLAYER_SIZE }));
	}

	void UpdatePlayer(Player& player, float timeDelta)
	{
		// Move player
		switch (player.direction)
		{
		case PlayerDirection::Up:
		{
			player.position.y -= player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Right:
		{
			player.position.x += player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Down:
		{
			player.position.y += player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Left:
		{
			player.position.x -= player.speed * timeDelta;
			break;
		}
		}
	}

	bool HasPlayerCollisionWithScreenBorder(const Player& player)
	{
		return !IsPointInRect(player.position, { 0.f, 0.f }, { (float)SCREEN_WIDTH, (float)SCREEN_HEGHT });
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(OurVectorToSf(player.position));

		const sf::Vector2f spriteScale = (GetSpriteScale(player.sprite, { PLAYER_SIZE, PLAYER_SIZE }));

		// We need to rotate and flip sprite to match player direction
		switch (player.direction)
		{
		case PlayerDirection::Up:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Right:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setScale(-spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		}

		window.draw(player.sprite);
	}
}
