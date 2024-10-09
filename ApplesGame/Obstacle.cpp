#include "Obstacle.h"

#include "Constans.h"

#include <cstdlib>
#include <assert.h>

namespace ApplesGame
{
	void InitObstacle(Obstacle& Obstacle, const sf::Texture& texture)
	{
		// Init sprite
		Obstacle.sprite.setTexture(texture);
		Obstacle.sprite.setOrigin(GetItemOrigin(Obstacle.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		Obstacle.sprite.setScale(GetSpriteScale(Obstacle.sprite, { OBSTACLE_SIZE, OBSTACLE_SIZE }));
	}

	void ResetObstacleState(Obstacle& Obstacle)
	{
		// init apple state
		Obstacle.position.x = (float)(rand() % SCREEN_WIDTH);
		Obstacle.position.y = (float)(rand() % SCREEN_HEGHT);
	}

	void DrawObstacle(Obstacle& Obstacle, sf::RenderWindow& window)
	{
		Obstacle.sprite.setPosition(OurVectorToSf(Obstacle.position));
		window.draw(Obstacle.sprite);
	}

	void ClearObstacleGrid(ObstacleGrid& ObstacleGrid)
	{
		ObstacleGrid.ObstacleCells.clear();
		ObstacleGrid.cells.clear();
	}

	void AddObstacleToGrid(ObstacleGrid& ObstacleGrid, Obstacle& Obstacle)
	{
		// Remove Obstacle from old cells
		RemoveObstacleFromGrid(ObstacleGrid, Obstacle);

		// Find new cells range
		Vector2Df appleCornerTL = Obstacle.position + Vector2Df{ -APPLE_SIZE / 2, -APPLE_SIZE / 2 };
		Vector2Df appleCornerBR = Obstacle.position + Vector2Df{ APPLE_SIZE / 2, APPLE_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_VERTICAL;
		int minCellX = std::max((int)(appleCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(appleCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(appleCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(appleCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		// Add Obstacle to new cells	
		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				ObstacleGrid.cells[{cellX, cellY}].insert(&Obstacle);
				ObstacleGrid.ObstacleCells.insert({ &Obstacle, {cellX, cellY} });
			}
		}
	}

	void RemoveObstacleFromGrid(ObstacleGrid& ObstacleGrid, Obstacle& Obstacle)
	{
		auto range = ObstacleGrid.ObstacleCells.equal_range(&Obstacle);
		for (auto it = range.first; it != range.second; ++it)
		{
			ObstacleGrid.cells[it->second].erase(&Obstacle);
		}
		ObstacleGrid.ObstacleCells.erase(range.first, range.second);
	}	

		bool FindPlayerCollisionWithObstacle(const Vector2Df& playerPosition, const ObstacleGrid& grid, ObstacleSet& result)
	{
			Vector2Df playerCornerTL = playerPosition + Vector2Df{ -PLAYER_SIZE / 2, -PLAYER_SIZE / 2 };
			Vector2Df playerCornerBR = playerPosition + Vector2Df{ PLAYER_SIZE / 2, PLAYER_SIZE / 2 };

			const float cellSizeX = (float)SCREEN_WIDTH / OBSTACLES_GRID_CELS_HORIZONTAL;
			const float cellSizeY = (float)SCREEN_WIDTH / OBSTACLES_GRID_CELS_VERTICAL;
			int minCellX = std::max((int)(playerCornerTL.x / cellSizeX), 0);
			int maxCellX = std::min((int)(playerCornerBR.x / cellSizeX), (int)OBSTACLES_GRID_CELS_HORIZONTAL - 1);
			int minCellY = std::max((int)(playerCornerTL.y / cellSizeY), 0);
			int maxCellY = std::min((int)(playerCornerBR.y / cellSizeY), (int)OBSTACLES_GRID_CELS_VERTICAL - 1);

			for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
			{
				for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
				{
					const auto it = grid.cells.find({ cellX, cellY });
					if (it == grid.cells.cend())
					{
						continue;
					}

					for (Obstacle* obstacle : it->second)
					{
						Vector2Df distance = playerPosition - obstacle->position;
						if (GetVectorLength(distance) < (PLAYER_SIZE + OBSTACLE_SIZE) / 2)
						{
							result.insert(obstacle);
						}
					}
				}
			}

			return result.size() > 0;
		//It works partially
		// 
		//Vector2Df playerRectTL = playerPosition + Vector2Df{ -PLAYER_SIZE / 2, -PLAYER_SIZE / 2 };
		//Vector2Df playerRectBR = playerPosition + Vector2Df{ PLAYER_SIZE / 2, PLAYER_SIZE / 2 };

		//const float cellSizeX = (float)SCREEN_WIDTH / OBSTACLES_GRID_CELS_HORIZONTAL;
		//const float cellSizeY = (float)SCREEN_HEGHT / OBSTACLES_GRID_CELS_VERTICAL;
		//int minCellX = std::max((int)(playerRectTL.x / cellSizeX), 0);
		//int maxCellX = std::min((int)(playerRectBR.x / cellSizeX), (int)OBSTACLES_GRID_CELS_HORIZONTAL - 1);
		//int minCellY = std::max((int)(playerRectTL.y / cellSizeY), 0);
		//int maxCellY = std::min((int)(playerRectBR.y / cellSizeY), (int)OBSTACLES_GRID_CELS_VERTICAL - 1);

		//for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		//{
		//	for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
		//	{
		//		const auto it = grid.cells.find({ cellX, cellY });
		//		if (it == grid.cells.cend())
		//		{
		//			continue;
		//		}

		//		for (Obstacle* obstacle : it->second)
		//		{
		//			Vector2Df obstacleRectTL = obstacle->position + Vector2Df{ -OBSTACLE_SIZE / 2, -OBSTACLE_SIZE / 2 };
		//			Vector2Df obstacleRectBR = obstacle->position + Vector2Df{ OBSTACLE_SIZE / 2, OBSTACLE_SIZE / 2 };

		//			// Проверка на пересечение прямоугольников
		//			if (playerRectTL.x < obstacleRectBR.x && playerRectBR.x > obstacleRectTL.x &&
		//				playerRectTL.y < obstacleRectBR.y && playerRectBR.y > obstacleRectTL.y)
		//			{
		//				result.insert(obstacle);
		//			}
		//		}
		//	}
		//}

		//return result.size() > 0;
	}
}