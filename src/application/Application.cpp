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

	renderer_ = new Renderer;

	ui_shader_ = Shader::CreateFromFiles("src/renderer/shaders/default/ui.vert", "src/renderer/shaders/default/ui.frag");
	ui_material_ = new UIMaterial(ui_shader_);
	ui_renderer_ = new BatchRenderer(ui_material_);
}

Application::~Application()
{
	delete ui_renderer_;
	delete ui_material_;
	delete ui_shader_;

	delete window_;
	delete renderer_;
}

void Application::Run()
{
	MainLoop();
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
			OnUpdate(time - 1.0);
			OnUIUpdate(ui_renderer_);

			updates++;
			time--;
		}

		OnRender(renderer_);
		OnUIRender(ui_renderer_);
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
