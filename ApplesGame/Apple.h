#pragma once
#include <SFML/Graphics.hpp>
#include "Constans.h"
#include "Math.h"
#include <unordered_map>
#include <unordered_set>

namespace ApplesGame
{
	struct Apple
	{
		Position position;
		sf::Sprite sprite;
		bool isEaten = false;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void ResetAppleState(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void MarkAppleAsEaten(Apple& apple);

	using ApplesSet = std::unordered_set<Apple*>;

	struct ApplesGrid
	{
		std::unordered_map<Vector2Di, ApplesSet> cells;
		std::unordered_multimap<Apple*, Vector2Di> appleCells;
	};

	void ClearApplesGrid(ApplesGrid& applesGrid);
	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple);
	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple);
	bool FindPlayerCollisionWithApples(const Vector2Df& playerPosition, const ApplesGrid& grid, ApplesSet& result);
}
