#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class MyDisplay
{
public:
	MyDisplay();
	~MyDisplay();
	void initMyDIsplay();
	void changeBuffer();
	void clearMyDisplay(float r, float g, float b, float a);

	float getWidth();
	float getHeight();

private:

	void returnError(std::string errorString);
	
	SDL_GLContext contextGL; //global variable to hold the context
	SDL_Window* winSDL; //holds pointer to out window
	
	//Screen dimensions
	float scrWidth;  
	float scrHeight;
};

