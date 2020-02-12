//
#pragma comment (lib, "winmm.lib")

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//C++ 
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <crtdbg.h>
#include <sstream>
#include <iomanip>
#include <thread>

//my 
#include "consts.h"
#include "game.h"
#include "object.h"
#include "terrain.h"
#include "character.h"
#include "Bullet.h"
#include "pickups.h"
#include "player.h"
#include "enemy.h"
