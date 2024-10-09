#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace ApplesGame
{
	struct Game;

	struct GameStateRecordsData
	{
		// Resources
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	void InitRecords(GameStateRecordsData& data, Game& game);
	void ShutdownRecords(GameStateRecordsData& data, Game& game);
	void HandleRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event);
	void UpdateRecords(GameStateRecordsData& data, Game& game, float timeDelta);
	void DrawRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window);
}
