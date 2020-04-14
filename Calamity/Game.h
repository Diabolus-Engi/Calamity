#pragma once
#include "Region.h"

struct Camera {
	Point2D pos;
	Camera() { pos.x = 0; pos.y = 0; }
	Camera(Point2D p) { pos = p; }
	Camera(int x, int y) { pos.x = x; pos.y = y; }
};

enum class GAME_STATE {
	RUNNING,
	CLOSING
};

class Game {
public:
	bool Update();
	void Render();
	
	// Constructors
	Game();

	GAME_STATE game_state;

	// Mouse/Keyboard cursor
	char cursor = 'X';
	Point2D cursor_pos;
	Point2D last_mouse_pos;

	// Player entity
	Entity* player = nullptr;
	Entity* selected_entity = nullptr;

	// Camera
	Camera camera;

	// Screen details
	static int SCREEN_WIDTH, SCREEN_HEIGHT;

	Point2D screen_to_world(int x, int y);
	Point2D screen_to_world(Point2D xy);

private:
	Region region;

};



