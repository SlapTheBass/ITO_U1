#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

#include "Utils.h"


/* DEBUG ONLY MACROS */
#ifdef  _DEBUG

#define DBG(x)  (std::cout << #x << " = " << x << std::endl);

#endif //  _DEBUG
