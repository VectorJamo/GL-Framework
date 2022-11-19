#include "application.h"

Application::Application()
	:window(nullptr), rect(nullptr), camera(nullptr)
{
}

Application::~Application()
{
	delete rect;

	Sprite::Free();
	delete camera;
	delete window;
}

void Application::Setup()
{
	window = new Window(SCRWIDTH, SCRHEIGHT, "OpenGL Framework");
	if (!window->Init())
	{
		std::cout << "Window initialization failed!" << std::endl;
		assert(false);
	}
	window->SetVSyncEnabled(true);

	// Initialze the systems
	Input::Init(window);
	Sprite::Init();

	camera = new OrthographicCamera(-400.0f, 400.0f, 300.0f, -300.0f, 1.0f, -1.0f);
	camera->SetZoomSpeed(50.0f);

	rect = new Sprite(-50.0f, 50.0f, 100.0f, 100.0f);
	rect->SetTexture("res/textures/chess.jpg");
}

void Application::Update()
{
	while (!window->IsClosed())
	{
		window->Clear(0.0f, 0.0f, 0.0f, 0.0f);
		HandleInput();

		// Draw
		rect->Draw();
		
		window->Display();
	}
}

void Application::HandleInput()
{
	window->PollEvents();
	camera->UpdateControls();
}
void Application::Run()
{
	Setup();
	Update();
}
