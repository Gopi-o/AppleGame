#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Vector2Df
	{
		float x = 0.f;
		float y = 0.f;
	};

	Vector2Df operator+(const Vector2Df& lhs, const Vector2Df& rhs);
	Vector2Df operator-(const Vector2Df& lhs, const Vector2Df& rhs);

	float GetVectorLength(const Vector2Df& vector);

	struct Vector2Di
	{
		int x = 0;
		int y = 0;
	};

	bool operator==(const Vector2Di& lhs, const Vector2Di& rhs);

	typedef Vector2Df Position;

	sf::Vector2f OurVectorToSf(const Vector2Df& v);
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2Df& desiredSize);
	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2Df& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

	// Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	bool IsPointInRect(Vector2Df point, Vector2Df rectTL, Vector2Df rectBR);
}

template<>
struct std::hash<ApplesGame::Vector2Di>
{
	std::size_t operator()(const ApplesGame::Vector2Di& v) const noexcept
	{
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};
