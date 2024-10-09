#pragma once

#include <SFML/Graphics.hpp>
#include "Constans.h"
#include "Math.h"
#include <unordered_map>
#include <unordered_set>

namespace ApplesGame
{
	struct Obstacle
	{
		Position position;
		sf::Sprite sprite;
	};

	void InitObstacle(Obstacle& Obstacle, const sf::Texture& texture);
	void ResetObstacleState(Obstacle& Obstacle);
	void DrawObstacle(Obstacle& Obstacle, sf::RenderWindow& window);

	using ObstacleSet = std::unordered_set<Obstacle*>;

	struct ObstacleGrid
	{
		std::unordered_map<Vector2Di, ObstacleSet> cells;
		std::unordered_multimap<Obstacle*, Vector2Di> ObstacleCells;
	};

	void ClearObstacleGrid(ObstacleGrid& ObstacleGrid);
	void AddObstacleToGrid(ObstacleGrid& ObstacleGrid, Obstacle& Obstacle);
	void RemoveObstacleFromGrid(ObstacleGrid& ObstacleGrid, Obstacle& Obstacle);
	bool FindPlayerCollisionWithObstacle(const Vector2Df& playerPosition, const ObstacleGrid& grid, ObstacleSet& result);
}
