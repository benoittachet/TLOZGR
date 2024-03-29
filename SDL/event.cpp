#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "DrawMap.h"
#include "Hero.h"
#include "Map.h"
#include "transitions.h"
#include <Windows.h>

extern std::vector<map> maps;

bool execEvent(SDL_Event event, void *data)
{
	DataToDraw *dat;
	dat = (DataToDraw *)data;
	int actualPosScreenX = (int)(dat->getHero()->getPosXScreen());
	int actualPosScreenY = (int)(dat->getHero()->getPosYScreen());
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (!dat->useObject)
	{
		//continuous-response keys
		if (keystate[SDL_SCANCODE_LEFT])
		{
			if (dat->getHero()->getPosX() >= 1)
			{
				if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY() - 1)][(int)(dat->getHero()->getPosX() - 0.125)] == 0)
				{
					dat->getHero()->setPosX(dat->getHero()->getPosX() - (float)0.125);
					if (dat->getHero()->getPosX() >= (dat->getMap()->getWidth() - 15))
						dat->getHero()->setPosXScreen(40 - dat->getMap()->getWidth() + dat->getHero()->getPosY());
					if (dat->getHero()->getPosX() <= 20)
						dat->getHero()->setPosXScreen(dat->getHero()->getPosX());
				}
				if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
					dat->setDrawAll(true);
			}
			else if (dat->getMap()->getMapWest())
			{
				dat->doTransition = -2;
			}
			if (dat->getHero()->getCount() > 2)
			{
				dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
				dat->getHero()->setCount(0);
				if (dat->getHero()->getActualImage() > 10)
					dat->getHero()->setActualImage(0);
			}
			else if (!keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN])
				dat->getHero()->setCount(dat->getHero()->getCount() + 1);
			if (!(keystate[SDL_SCANCODE_UP]) && !(keystate[SDL_SCANCODE_DOWN]))
				dat->getHero()->setActualPos(1);
			dat->needDraw = true;
		}
		if (keystate[SDL_SCANCODE_RIGHT])
		{
			if (dat->getHero()->getPosX() < (dat->getMap()->getWidth() - 1))
			{
				if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY() - 1)][(int)(dat->getHero()->getPosX() + 0.125)] == 0)
				{
					dat->getHero()->setPosX(dat->getHero()->getPosX() + (float)0.125);
					if (dat->getHero()->getPosX() >= (dat->getMap()->getWidth() - 15))
						dat->getHero()->setPosXScreen(40 - dat->getMap()->getWidth() + dat->getHero()->getPosY());
					if (dat->getHero()->getPosX() <= 20)
						dat->getHero()->setPosXScreen(dat->getHero()->getPosX());
				}
			}
			else if (dat->getMap()->getMapEast() != NULL)
			{
				dat->doTransition = 2;
			}
			if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
				dat->setDrawAll(true);
			if (dat->getHero()->getCount() > 2)
			{
				dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
				dat->getHero()->setCount(0);
				if (dat->getHero()->getActualImage() > 10)
					dat->getHero()->setActualImage(0);
			}
			else if (!keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN])
				dat->getHero()->setCount(dat->getHero()->getCount() + 1);
			if (!keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN])
				dat->getHero()->setActualPos(3);
			dat->needDraw = true;
		}
		if (keystate[SDL_SCANCODE_UP])
		{
			if (dat->getHero()->getPosY() >= 3)
			{
				if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY() - 1.5)][(int)(dat->getHero()->getPosX())] == 0)
				{
					dat->getHero()->setPosY(dat->getHero()->getPosY() - (float)(0.125));
					if (dat->getHero()->getPosY() >= dat->getMap()->getHeight() - 15)
						dat->getHero()->setPosYScreen(30 - dat->getMap()->getHeight() + dat->getHero()->getPosY());
					if (dat->getHero()->getPosY() <= 15)
						dat->getHero()->setPosYScreen(dat->getHero()->getPosY());
				}
			}
			else if (dat->getMap()->getMapNorth() != NULL)
			{
				dat->doTransition = -1;
			}
			if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
				dat->setDrawAll(true);
			if (dat->getHero()->getCount() > 2)
			{
				dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
				dat->getHero()->setCount(0);
				if (dat->getHero()->getActualImage() > 10)
					dat->getHero()->setActualImage(0);
			}
			dat->getHero()->setCount(dat->getHero()->getCount() + 1);
			dat->getHero()->setActualPos(2);
			dat->needDraw = true;
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			if (dat->getHero()->getPosY() < dat->getMap()->getHeight() - .125)
			{
				if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY() + 0.125)][(int)(dat->getHero()->getPosX())] == 0)
				{
					dat->getHero()->setPosY(dat->getHero()->getPosY() + (float)(0.125));
					if (dat->getHero()->getPosY() >= dat->getMap()->getHeight() - 15)
						dat->getHero()->setPosYScreen(30 - dat->getMap()->getHeight() + dat->getHero()->getPosY());
					if (dat->getHero()->getPosY() <= 15)
						dat->getHero()->setPosYScreen(dat->getHero()->getPosY());
				}
			}
			else if (dat->getMap()->getMapSouth() != NULL)
			{
				dat->doTransition = 1;
			}
			if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
				dat->setDrawAll(true);
			if (dat->getHero()->getCount() > 2)
			{
				dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
				dat->getHero()->setCount(0);
				if (dat->getHero()->getActualImage() > 10)
					dat->getHero()->setActualImage(0);
			}
			else
				dat->getHero()->setCount(dat->getHero()->getCount() + 1);
			dat->getHero()->setActualPos(0);
			dat->needDraw = true;
		}




		if (keystate[SDL_SCANCODE_1])//objet 1
		{
			use_objet(dat->getHero()->getObj1(), dat);
			while (keystate[SDL_SCANCODE_1])
			{
				SDL_PollEvent(&event);
				keystate = SDL_GetKeyboardState(NULL);
			}
		}
		else if (keystate[SDL_SCANCODE_2])//objet 2
		{
			use_objet(dat->getHero()->getObj2(), data);
			while (keystate[SDL_SCANCODE_2])
			{
				SDL_PollEvent(&event);
				keystate = SDL_GetKeyboardState(NULL);
			}
		}
		else if (keystate[SDL_SCANCODE_5])
		{
			dat->getHero()->setObj1(dat->getHero()->getObj1() - 1);
			while (keystate[SDL_SCANCODE_5])
			{
				SDL_PollEvent(&event);
				keystate = SDL_GetKeyboardState(NULL);
			}
		}
		else if (keystate[SDL_SCANCODE_6])
		{
			dat->getHero()->setObj1(dat->getHero()->getObj1() + 1);
			while (keystate[SDL_SCANCODE_6])
			{
				SDL_PollEvent(&event);
				keystate = SDL_GetKeyboardState(NULL);
			}
		}
		if (!dat->getHero()->getActualImage() == 0)
		if (!dat->useObject && !(keystate[SDL_SCANCODE_LEFT]) && !(keystate[SDL_SCANCODE_RIGHT]) && !(keystate[SDL_SCANCODE_UP]) && !(keystate[SDL_SCANCODE_DOWN]))
		{
			dat->getHero()->setActualImage(0);
			dat->needDraw = true;
		}
	}
	switch (event.type)
	{
	case SDL_QUIT:
		closeWindow(dat->getWindow());
		return (true);
		break;
	default:
		break;
	}
	
	return (false);
}