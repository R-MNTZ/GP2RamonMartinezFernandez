#include "MyDisplay.h"


MyDisplay::MyDisplay()
{
	winSDL = nullptr; //initialise to generate null access violation for debugging. 
	scrWidth = 1024.0f;
	scrHeight = 768.0f; 
}

MyDisplay::~MyDisplay()
{
	SDL_GL_DeleteContext(contextGL); // delete context
	SDL_DestroyWindow(winSDL); // detete window (make sure to delete the context and the window in the opposite order of creation in initMyDIsplay())
	SDL_Quit();
}

float MyDisplay::getWidth() { return scrWidth; } //getters
float MyDisplay::getHeight() { return scrHeight; }

void MyDisplay::returnError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void MyDisplay::changeBuffer()
{
	SDL_GL_SwapWindow(winSDL); //swap buffers
}

void MyDisplay::clearMyDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void MyDisplay::initMyDIsplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	winSDL = SDL_CreateWindow("Kachow!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)scrWidth, (int)scrHeight, SDL_WINDOW_OPENGL); // create window

	if (winSDL == nullptr)
	{
		returnError("window failed to create");
	}

	contextGL = SDL_GL_CreateContext(winSDL);

	if (contextGL == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont form faces that are not pointing at the camera

	
}