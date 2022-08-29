#include "App.h"

int main()
{
	srand(static_cast<int>(time(nullptr)));  //random seed depends on processor time

	App* application = new App();

	application->Run();
}