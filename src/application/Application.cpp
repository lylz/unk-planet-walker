#include "Application.h"
#include "Timer.h"

Application::Application(std::string name, int width, int height)
	: name_(name),
      width_(width),
      height_(height),
      application_settings_(ApplicationSettings(width, height)),
      window_(Window(name_.c_str(), width_, height_))
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		printf("ERROR: unable to initialize glew. \n");
		exit(EXIT_FAILURE);
	}
}

void Application::Run()
{
	Init();
	MainLoop();
}

void Application::AddLayer(Layer *layer)
{
	layers_.push_back(layer);
	layer->Init();
}

void Application::RemoveLayer(Layer *layer)
{
	for (size_t i = 0; i < layers_.size(); i++)
	{
		if (layers_[i] == layer)
		{
			layers_.erase(layers_.begin() + i);
			break;
		}
	}
}

ApplicationSettings *Application::application_settings()
{
    return &application_settings_;
}

void Application::MainLoop()
{
	using namespace std::chrono;

	int updates = 0;
	int frames = 0;
	int fps = 0;
	int ups = 0;

	Timer timer;
	float update_tick = 1000.0f / 60.0f;
	long double update_time = timer.GetElapsedTime();
	long double tick_timer = 0;

	while (!window_.ShouldClose() && !application_settings_.should_close)
	{
		window_.Update();

		long double update_delta_time = timer.GetElapsedTime() - update_time;

		if (update_delta_time > update_tick)
		{
			Update(update_delta_time);

			updates++;
			update_time += update_tick;
		}

		Timer frame_timer;
		Render();
		window_.SwapBuffers();
		frames++;
		//printf("Frame Time: %.4f ms. UPS: %d, FPS: %d\n", frame_timer.GetElapsedTime(), ups, fps);

		if (timer.GetElapsedTime() - tick_timer > 1000.0f)
		{
			tick_timer += 1000.0f;

			printf("FPS: %d, UPS: %d\n", frames, updates);

			ups = updates;
			fps = frames;

			updates = 0;
			frames = 0;
		}
	}
}

void Application::Init()
{
	OnInit();
}

void Application::Update(long double dt)
{
    OnUpdate(dt);

	for (size_t i = 0; i < layers_.size(); i++)
	{
		layers_[i]->OnUpdate();
	}
}

void Application::Render()
{
	GLWCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLWCall(glClearColor(0.0, 0.0, 0.0, 1.0));

	for (size_t i = 0; i < layers_.size(); i++)
	{
		if (layers_[i]->visible())
		{
			layers_[i]->OnRender();
		}
	}
}
