#pragma once
#include <string>

namespace ApplesGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 20.f;
	const float APPLE_SIZE = 20.f;
	const float OBSTACLE_SIZE = 20.f;
	const float INITIAL_SPEED = 100.f;
	const float ACCELERATION = 10.f; // For each eaten apple player speed will be increased by this value
	const int MIN_APPLES = 20;
	const int MAX_APPLES = 80;
	const int MIN_OBSTACLES = 10;
	const int MAX_OBSTACLES = 30;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;

	const unsigned int APPLES_GRID_CELLS_HORIZONTAL = unsigned(SCREEN_WIDTH / (APPLE_SIZE * 4));
	const unsigned int APPLES_GRID_CELLS_VERTICAL = unsigned(SCREEN_HEGHT / (APPLE_SIZE * 4));

	const unsigned int OBSTACLES_GRID_CELS_HORIZONTAL = unsigned(SCREEN_WIDTH / (OBSTACLE_SIZE * 4));
	const unsigned int OBSTACLES_GRID_CELS_VERTICAL = unsigned(SCREEN_HEGHT / (OBSTACLE_SIZE * 4));

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some SPP
}
