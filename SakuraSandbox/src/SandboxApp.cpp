#define SAKURA_ENTRY_POINT
#include <SakuraEngine.h>

class SandboxApp : public Sakura::Application
{
public:
	SandboxApp() = default;
	virtual ~SandboxApp() = default;
};

Sakura::Application* Sakura::CreateApplication()
{
	return new SandboxApp();
}