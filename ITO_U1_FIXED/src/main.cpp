#include "App.h"

int main()
{
	srand(static_cast<int>(time(nullptr)));

	App* application = new App();

	application->Run();
}