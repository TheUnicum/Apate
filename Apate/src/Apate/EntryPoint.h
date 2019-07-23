#pragma once

#ifdef AP_PLATFORM_WINDOWS

extern Apate::Application* Apate::CreateApplication();

int main(int argc, char** arv)
{
	auto app = Apate::CreateApplication();
	app->Run();
	delete app;
}

#endif // AP_PLATFORM_WINDOWS
