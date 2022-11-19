#pragma once
#include "core.h"

#include <cassert>
#include <memory>

#define SCRWIDTH 800
#define SCRHEIGHT 600

class Application
{
private:
	Window* window;
	Sprite* rect;

	OrthographicCamera* camera;

public:
	Application();
	~Application();

	void Setup();
	void Update();
	void HandleInput();

	void Run();
};

