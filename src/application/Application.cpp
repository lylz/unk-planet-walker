#include "Application.h"

Application::Application(std::string name, int width, int height)
	: name_(name), width_(width), height_(height)
{
	window_ = new Window(name_.c_str(), width_, height_);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		printf("ERROR: unable to initialize glew. \n");
		exit(EXIT_FAILURE);
	}
}

Application::~Application()
{
	delete window_;
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

void Application::MainLoop()
{
	using namespace std::chrono;

	int updates = 0;
	int frames = 0;
	int fps = 0;
	int ups = 0;

	long double ns = (double)1000000000 / 30;
	long double previous_time = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
	long double time = duration_cast<nanoseconds>(system_clock::duration::zero()).count();
	milliseconds timer = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	while (!window_->ShouldClose())
	{
		window_->Update();

		long double current_time = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
		long double frame_time = current_time - previous_time;
		time += frame_time / ns;
		previous_time = current_time;

		//printf("Frame Time: %.4f ms. UPS: %d, FPS: %d\n", (double)frame_time / 1000000, ups, fps);

		if (time >= 1.0)
		{
			Update(time - 1.0);

			updates++;
			time--;
		}

		Render();
		window_->SwapBuffers();
		frames++;

		if (duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - timer > (milliseconds)1000)
		{
			timer += (milliseconds)1000;

			printf("UPS: %d\n", updates);
			printf("FPS: %d\n", frames);

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
	for (size_t i = 0; i < layers_.size(); i++)
	{
		layers_[i]->OnUpdate();
	}
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	for (size_t i = 0; i < layers_.size(); i++)
	{
		if (layers_[i]->visible())
		{
			layers_[i]->OnRender();
		}
	}
}
