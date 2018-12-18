#include "GameScene.h"
#include "MainCamera.h"
#include "MyMesh.h"
#include "TextDisplay.h"
#include <iostream>
#include <string>










GameScene::GameScene()
{
	_gameStatus = GameStatus::PLAY; //Set status to PLAY
	MyDisplay* _presentGame = new MyDisplay(); //new display

}

GameScene::~GameScene()
{
}

void GameScene::gameSceneRun()
{
	startSystems();
	mainGameLoop();
	
}

void GameScene::startSystems()
{
	//Initialise display and models, textures and shaders
	_presentGame.initMyDIsplay(); 
	monkeyMesh.prepareModel("..\\res\\monkey3.obj");
	texture.initTex("..\\res\\bricks.jpg"); //
	shader.init("..\\res\\shader"); //new shader
	
	ceilingMesh.prepareModel("..\\res\\cube.obj");
    texture2.initTex("..\\res\\water.jpg"); 

	bulletMesh.prepareModel("..\\res\\cube.obj");
   
	
	
	/*
	floorMesh.prepareModel("..\\res\\cube.obj");
	texture2.initTex("..\\res\\sky.png");
	
	northwallMesh.prepareModel("..\\res\\cube.obj");
	//textureNw.initTex("..\\res\\sky.png");

	southwallMesh.prepareModel("..\\res\\cube.obj");
	textureNw.initTex("..\\res\\water.jpg");

	eastwallMesh.prepareModel("..\\res\\cube.obj");
	textureNw.initTex("..\\res\\water.jpg");

	westwallMesh.prepareModel("..\\res\\cube.obj");
	textureNw.initTex("..\\res\\water.jpg");
	*/

	eggMesh.prepareModel("..\\res\\peanut.obj");
	texture3.initTex("..\\res\\peanut.jpg"); //

	//Initialise camera
	camera1.startMainCamera(glm::vec3(0, 0, -25), 70.0f, (float)_presentGame.getWidth()/_presentGame.getHeight(), 0.01f, 1000.0f);
		
	//Display message with controls
	std::cout << "Controls: WASD to move" << endl;
	std::cout << "Q to rotate monkey" << endl;
	std::cout << "X and C to move camera forwards and backwards" << endl;
	std::cout << "Space to shoot" << endl;
}

void GameScene::mainGameLoop()
{//Run all essential methods while status isn't exit 
	while (_gameStatus != GameStatus::EXIT)
	{
		
		processInput();
		updateTransform();
		drawMainGame();
		moveBullet();
		if (checkCol(bulletMesh.getSpherePos(), 5.0f, eggMesh.getSpherePos(), 5.0f) == true) {
			
				//Move the egg if it gets shot
				eggX = -20 + (std::rand() % (20 - -20 + 1));
		} 
		
	}
	
}

void GameScene::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_KEYDOWN: //Keyboard input
			if (evnt.key.keysym.sym == SDLK_d) {
				//if (movX < -10.0f) {  //Clamp for the object movement
				//	movX = -10.0f;
				//}
				//Move object to the right
				movX -= 0.2;
				//Make it face right
				rotY = -1.67;
				lookRight = true;
				lookLeft = false;
				//Move camera alongside monkey
				camera1.MoveLeft(0.2);

			}
			if (evnt.key.keysym.sym == SDLK_a) {

				//if (movX > 10.0f) {
				//	movX = 10.0f;
				//}
				//Move object to the Right
				movX += 0.2;
				//Make it face right
				rotY = 1.67;
				lookRight = false;
				lookLeft = true;
				//Move camera alongside monkey
				camera1.MoveRight(0.2);

			}
			if (evnt.key.keysym.sym == SDLK_w) {
				//if (movY > 8.6f) {
				//	movY = 8.6f;
				//}
				//Move Object up
				movY += 0.2;
				//Re-set rotation
				rotY = 0;
				//Move camera alongside monkey
				camera1.MoveUp(0.2);
				lookRight = false;
				lookLeft = false;
			}
			if (evnt.key.keysym.sym == SDLK_s) {
				//if (movY < -10.0f) {
				//	movY = -10.0f;
				//}
				//Move Object down
				movY -= 0.2;
				//Re-set rotation
				rotY = 0;
				lookRight = false;
				lookLeft = false;
				//Move camera alongside monkey
				camera1.MoveDown(0.2);
			}

			if (evnt.key.keysym.sym == SDLK_q) {
				//Increase the monkey's rotation's x value
				rotX += 0.1;
			}

			if (evnt.key.keysym.sym == SDLK_x) {
				camera1.MoveForward(cameraSpeed);
			}

			if (evnt.key.keysym.sym == SDLK_c) {
				camera1.MoveBackwards(cameraSpeed);
			}

			if (evnt.key.keysym.sym == SDLK_v) {
				//Rotate camera on x-axis
				camera1.Pitch(0.08);
			}

			//Call shoot left or right
			if (evnt.key.keysym.sym == SDLK_SPACE) {
				if (lookLeft == true) {
					shoot('l');
				}
				else if (lookRight == true) {
					shoot('r');
				}
	
			}



			break;



// If we quit SDL status is set to exit
		case SDL_QUIT:
			_gameStatus = GameStatus::EXIT;
			break;

		default:
			break;
		}
	}

}


void GameScene::drawMainGame()
{
	//Clear the display
	_presentGame.clearMyDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	//Bind shaders, update shaders, bind textures and draw models
	shader.BindShader();
	shader.Update(monkeyMesh.transformMonkey, camera1);
	texture.TexBind(0);
	monkeyMesh.form();
	
	shader.Update(bulletMesh.transformBullet, camera1);
	texture.TexBind(0);
	bulletMesh.form();
	
	shader.Update(ceilingMesh.transformCeiling, camera1);
	texture2.TexBind(0);
	ceilingMesh.form();

	shader.Update(eggMesh.transformEgg, camera1);
	texture3.TexBind(0);
	eggMesh.form();

	//Enable GL_COLOR_ARRAY
	glEnableClientState(GL_COLOR_ARRAY); 
	//glEnd();

	_presentGame.changeBuffer();
	
} 

bool GameScene::checkCol(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	//Take the distance between the objects
	float distX = m1Pos.x - m2Pos.x;
	float distY = m1Pos.y - m2Pos.y;
	float distZ = m1Pos.z - m2Pos.z;
	float distTotal = sqrt((distX*distX) + (distY*distY) + (distZ*distZ));

	//If its bigger than the radius no collision
	if (distTotal > m1Rad) {
		return false;
	}
	//If its smaller there has been a collision
	else if (distTotal < m1Rad) {
		return true;
	}
}
/*
void GameScene ::setFog() {
	//Not implemented

	float fogColor[4] = { 0 , 0 , 0 , 1.0 };
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, -30.0);
	glFogf(GL_FOG_END, 6.0);
	//	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 1.0);
	glFogfv(GL_FOG_COLOR, fogColor);
	

}
*/
void GameScene::shoot(char direction) {
	if (direction == 'l') {
		//Move bullet to the monkey's position
		initialBulletPosx = movX;
		initialBulletPosy = movY;
		shootLeft = true;
		shootRight = false;
		
	}
	else if (direction == 'r') {
		//Move bullet to the monkey's position
		initialBulletPosx = movX;
		initialBulletPosy = movY;
		shootRight = true;
		shootLeft = false;
	}
}

void GameScene::moveBullet() {
	if (shootRight == true) {
		initialBulletPosx -= 0.05;
	}
	else if (shootLeft == true) {
		initialBulletPosx += 0.05;
	}

}

void GameScene::updateTransform() {
	
	//Setting the position
	monkeyMesh.transformMonkey.SetPosition(glm::vec3(movX, movY, 0));
	//Setting th rotation
	monkeyMesh.transformMonkey.SetRotation(glm::vec3(rotX, rotY, rotZ));
	//Setting the scale
	monkeyMesh.transformMonkey.SetScale(glm::vec3(1, 1, 1));

	bulletMesh.transformBullet.SetPosition(glm::vec3(initialBulletPosx, initialBulletPosy, 0));
	bulletMesh.transformBullet.SetRotation(glm::vec3(0, 0, 0));
	bulletMesh.transformBullet.SetScale(glm::vec3(0.1, 0.1, 0.1));

	ceilingMesh.transformCeiling.SetPosition(glm::vec3(0, 0, sbPos));
	ceilingMesh.transformCeiling.SetRotation(glm::vec3(0, 0, 0));
	ceilingMesh.transformCeiling.SetScale(glm::vec3(sbScale, sbScale, 1));

	eggMesh.transformEgg.SetPosition(glm::vec3(eggX, 0, 0));
	eggMesh.transformEgg.SetRotation(glm::vec3(0, 0, 0));
	eggMesh.transformEgg.SetScale(glm::vec3(1, 1 , 1));

	

	//Update spheres of objects that can collide
	bulletMesh.updateSphere(*bulletMesh.transformBullet.GetPosition(), 1.0);
	//The position of the sphere is modified because the model's centre is set to its top, not its centre
	eggMesh.updateSphere(glm::vec3(eggX, -5, 0), 5);



	
}

