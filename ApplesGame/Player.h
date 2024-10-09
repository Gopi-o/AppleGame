#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

namespace ApplesGame
{
	enum class PlayerDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	struct Player
	{
		Position position;
		float speed = 0.f; // Pixels per second
		PlayerDirection direction = PlayerDirection::Up;
		sf::Sprite sprite;
	};

	void InitPlayer(Player& player, const sf::Texture& texture);
	void UpdatePlayer(Player& player, float timeDelta);

	bool HasPlayerCollisionWithScreenBorder(const Player& player);

	void DrawPlayer(Player& player, sf::RenderWindow& window);
}
