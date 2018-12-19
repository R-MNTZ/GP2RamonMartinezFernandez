#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "MyDisplay.h"
#include "MyShader.h"
#include "MyMesh.h"
#include "TextureClass.h"
#include "transform.h"
#include "Audio.h"

enum class GameStatus{PLAY, EXIT};

class GameScene
{
public:
	GameScene();
	~GameScene();

	void gameSceneRun();
	void setFog();
	void shoot(char direction);
	void moveBullet();

	void updateTransform();




private:

	void startSystems();
	void processInput(); 
	void mainGameLoop();
	void drawMainGame();

	bool checkCol(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

	MyDisplay _presentGame;
	GameStatus _gameStatus;
	//Meshes for the game objects
	MyMesh monkeyMesh;
	MyMesh ceilingMesh;
	MyMesh eggMesh;
	MyMesh bulletMesh;

	//Camera
	MainCamera camera1;

	//Textues for game objects 
	TextureClass texture; 
	TextureClass texture2;
	TextureClass texture3;
	TextureClass texture4;
	TextureClass textureNw;


	MyShader shader;


	
	//Audio
	unsigned int whistle;
	unsigned int backGroundMusic;

	//bools used for shooting
	bool shootRight = false;
	bool shootLeft = false;
	bool lookLeft = false;
	bool lookRight = false;

	//these are set to the position, scale and rotation of various game objects
	float movX = 0;
	float movY = 0;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;
	float initialBulletPosx = 100;
	float initialBulletPosy = 0;
	float eggX = 12;
	float sbPos = 50;
	float sbScale = 100;
	
	//Camera's movement speed
    float cameraSpeed = 0.5;

	

};

