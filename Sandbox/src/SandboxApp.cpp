#include "Apate.h"

class Sandbox : public Apate::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Apate::Application* Apate::CreateApplication()
{
	return new Sandbox();
}
