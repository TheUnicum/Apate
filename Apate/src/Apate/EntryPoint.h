#pragma once

#ifdef AP_PLATFORM_WINDOWS

extern Apate::Application* Apate::CreateApplication();

int main(int argc, char** arv)
{
	const char* iniFile = "../Apate/config/configFile.ini";
	INIReader reader(iniFile);

	Apate::Log::Init(static_cast<spdlog::level::level_enum>(reader.GetInteger("Generic", "LOG_LEVEL", 1)));
	AP_CORE_WARN("Initialized Log!");
	int a = 5;
	AP_INFO("Hello Test message INFO! Var={0}", a);

	if (reader.ParseError() < 0)
		AP_CORE_ERROR("Can't load <{0}> file!", iniFile);

	AP_CORE_DEBUG("Apate test INIReader file!");
	AP_CORE_DEBUG("  <integer> Log Level: {0}", reader.GetInteger("Generic", "LOG_LEVEL", -1));
	AP_CORE_DEBUG("  <integer> Version: {0}", reader.GetInteger("protocol", "version", -1));
	AP_CORE_DEBUG("  <string>  name: {0}", reader.Get("user", "name", "UNKNOWN"));
	AP_CORE_DEBUG("  <string>  email: {0}", reader.Get("user", "email", "UNKNOWN"));
	AP_CORE_DEBUG("  <real>    pi: {0}", reader.GetReal("user", "pi", -1));
	AP_CORE_DEBUG("  <bool>    active: {0}", reader.GetBoolean("user", "active", true));

	auto app = Apate::CreateApplication();
	app->Run();
	delete app;
}

#endif // AP_PLATFORM_WINDOWS
