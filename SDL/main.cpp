#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "DrawMap.h"
#include <windows.h>
#include <fstream>
#include "Map.h"
#include "Hero.h"
#include "event.h"
#include <SDL2/SDL_thread.h>

enum tilesets { eTDesert, eTForet, eTGrottes, eTHouse1, eTHouse2, eTHouse3, eTHouse4, eTHouse5, eTLac, eTMarais, eTMontagne, eTPlaines, eTD1, eTD2, eTD3, eTD4, eTD5, eTD6, eTD7, eTD8, eTD9, eTD10OUT, eTD10 };
std::vector<std::string> tilesetNames;
std::vector<int> tilesetWidths;
std::vector<int> tilesetHeights;
enum link_walk { idle = 0, walk1, walk2, walk3, walk4, walk5, walk6, walk7, walk8, walk9, walk10 };

void initTilesetData()
{
	tilesetNames.push_back("out/desert.png");
	tilesetNames.push_back("out/foret.png");
	tilesetNames.push_back("out/grottes.png");
	tilesetNames.push_back("out/house01.png");
	tilesetNames.push_back("out/house02.png");
	tilesetNames.push_back("out/house03.png");
	tilesetNames.push_back("out/house04.png");
	tilesetNames.push_back("out/house05.png");
	tilesetNames.push_back("out/lac.png");
	tilesetNames.push_back("out/marais.png");
	tilesetNames.push_back("out/montagne.png");
	tilesetNames.push_back("out/plaines.png");
	tilesetNames.push_back("donjons/Donjon1.png");
	tilesetNames.push_back("donjons/Donjon2.png");
	tilesetNames.push_back("donjons/Donjon3.png");
	tilesetNames.push_back("donjons/Donjon4.png");
	tilesetNames.push_back("donjons/Donjon5.png");
	tilesetNames.push_back("donjons/Donjon6.png");
	tilesetNames.push_back("donjons/Donjon7.png");
	tilesetNames.push_back("donjons/Donjon8.png");
	tilesetNames.push_back("donjons/Donjon9.png");
	tilesetNames.push_back("donjons/Donjon10out.png");
	tilesetNames.push_back("donjons/Donjon10.png");
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(60);
	tilesetWidths.push_back(44);
	tilesetWidths.push_back(16);
	tilesetWidths.push_back(24);
	tilesetWidths.push_back(24);
	tilesetWidths.push_back(22);
	tilesetWidths.push_back(24);
	tilesetWidths.push_back(24);
	tilesetWidths.push_back(22);
	tilesetWidths.push_back(80);
	tilesetWidths.push_back(40);
	tilesetWidths.push_back(40);
	tilesetHeights.push_back(64);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(32);
	tilesetHeights.push_back(64);
	tilesetHeights.push_back(42);
	tilesetHeights.push_back(54);
	tilesetHeights.push_back(16);
	tilesetHeights.push_back(16);
	tilesetHeights.push_back(20);
	tilesetHeights.push_back(14);
	tilesetHeights.push_back(14);
	tilesetHeights.push_back(20);
	tilesetHeights.push_back(10);
	tilesetHeights.push_back(40);
	tilesetHeights.push_back(60);
}

int main(int argc, char *argv[]) 
{
	initTilesetData();//initialisation des donn�es des tilesets : noms, taille
	SDL_Window *window;
	std::vector<map> maps;
	maps = init_maps_out();
	
	int i = 0;
	if ((window = initWindow()) == NULL)
		return -1;
	SDL_Event event;
	Hero hero(10, 7, maps[7]);
	bool exit_program = false;
	DataToDraw dat(&(maps[7]), window, &hero, true);
	init(&dat);
	DrawMap(&dat, 0, 0);
	dat.setDrawAll(false);
	while (!exit_program)
	{
		Uint32 time = SDL_GetTicks();
		SDL_PollEvent(&event);
		exit_program = execEvent(event, (void *)(&dat));
		time = SDL_GetTicks() - time;
		if (time < 15)
			Sleep((15 - time));
	}
	destroy(&dat);
	return 0;
}