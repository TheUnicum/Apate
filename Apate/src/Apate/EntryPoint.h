#pragma once

#ifdef AP_PLATFORM_WINDOWS

extern Apate::Application* Apate::CreateApplication();

int main(int argc, char** arv)
{
	Apate::Log::Init();
	AP_CORE_WARN("Initialize Log!");
	int a = 5;
	AP_INFO("Hello! Var={0}", a);

	auto app = Apate::CreateApplication();
	app->Run();
	delete app;
}

#endif // AP_PLATFORM_WINDOWS
