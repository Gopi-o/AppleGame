#include "Apple.h"
#include "Constans.h"

#include <cstdlib>
#include <assert.h>

namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		// Init sprite
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
		{
			return;
		}

		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}

	void ResetAppleState(Apple& apple)
	{
		// init apple state
		apple.position.x = (float)(rand() % SCREEN_WIDTH);
		apple.position.y = (float)(rand() % SCREEN_HEGHT);
		apple.isEaten = false;
	}

	void ClearApplesGrid(ApplesGrid& applesGrid)
	{
		applesGrid.appleCells.clear();
		applesGrid.cells.clear();
	}

	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		// Remove apple from old cells
		RemoveAppleFromGrid(applesGrid, apple);

		// Find new cells range
		Vector2Df appleCornerTL = apple.position + Vector2Df{ -APPLE_SIZE / 2, -APPLE_SIZE / 2 };
		Vector2Df appleCornerBR = apple.position + Vector2Df{ APPLE_SIZE / 2, APPLE_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_VERTICAL;
		int minCellX = std::max((int)(appleCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(appleCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(appleCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(appleCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		// Add apple to new cells	
		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				applesGrid.cells[{cellX, cellY}].insert(&apple);
				applesGrid.appleCells.insert({ &apple, {cellX, cellY} });
			}
		}
	}

	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		auto range = applesGrid.appleCells.equal_range(&apple);
		for (auto it = range.first; it != range.second; ++it)
		{
			applesGrid.cells[it->second].erase(&apple);
		}
		applesGrid.appleCells.erase(range.first, range.second);
	}

	bool FindPlayerCollisionWithApples(const Vector2Df& playerPosition, const ApplesGrid& grid, ApplesSet& result)
	{
		Vector2Df playerCornerTL = playerPosition + Vector2Df{ -PLAYER_SIZE / 2, -PLAYER_SIZE / 2 };
		Vector2Df playerCornerBR = playerPosition + Vector2Df{ PLAYER_SIZE / 2, PLAYER_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_VERTICAL;
		int minCellX = std::max((int)(playerCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(playerCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(playerCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(playerCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				const auto it = grid.cells.find({ cellX, cellY });
				if (it == grid.cells.cend())
				{
					continue;
				}

				for (Apple* apple : it->second)
				{
					Vector2Df distance = playerPosition - apple->position;
					if (GetVectorLength(distance) < (PLAYER_SIZE + APPLE_SIZE) / 2)
					{
						result.insert(apple);
					}
				}
			}
		}

		return result.size() > 0;
	}
}
