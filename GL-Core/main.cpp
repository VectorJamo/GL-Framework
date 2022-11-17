#include "src/application.h"

int main()
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	app->Run();

	return 0;
}