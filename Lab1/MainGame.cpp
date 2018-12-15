#include "GameScene.h"
#include "MainCamera.h"
#include "MyMesh.h"
#include "TextDisplay.h"
#include <iostream>
#include <string>










GameScene::GameScene()
{
	_gameStatus = GameStatus::PLAY;
	MyDisplay* _presentGame = new MyDisplay(); //new display
	

   // MyMesh* monkeyMesh();
	//MyMesh* mesh2();
	//TextureClass* texture();
	//TextureClass* texture2();
	//MyShader* shader();
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
	
	_presentGame.initMyDIsplay(); 
	//monkeyMesh.initTex(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0])); //size calcuated by number of bytes of an array / no bytes of one element
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

	camera1.startMainCamera(glm::vec3(0, 0, -25), 70.0f, (float)_presentGame.getWidth()/_presentGame.getHeight(), 0.01f, 1000.0f);
	//camera2.startMainCamera(glm::vec3(1, 1, -15), 70.0f, (float)_presentGame.getWidth() / _presentGame.getHeight(), 0.01f, 1000.0f);
	
	
	
}

void GameScene::mainGameLoop()
{
	while (_gameStatus != GameStatus::EXIT)
	{
		
		processInput();
		updateTransform();
		drawMainGame();
		moveBullet();
		if (checkCol(bulletMesh.getSpherePos(), 5.0f, eggMesh.getSpherePos(), 5.0f) == true) {
			
				//Move the egg if it gets shot
				eggX = 100;
				
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
				//Mak it face right
				rotY = -1.67;
				lookRight = true;
				lookLeft = false;
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
				camera1.MoveDown(0.2);
			}

			if (evnt.key.keysym.sym == SDLK_q) {
				rotX += 0.1;
			}

			if (evnt.key.keysym.sym == SDLK_x) {
				camera1.MoveForward(cameraSpeed);
			}

			if (evnt.key.keysym.sym == SDLK_c) {
				camera1.MoveBackwards(cameraSpeed);
			}

			if (evnt.key.keysym.sym == SDLK_v) {
				camera1.Pitch(0.08);
			}


			if (evnt.key.keysym.sym == SDLK_SPACE) {
				if (lookLeft == true) {
					shoot('l');
				}
				else if (lookRight == true) {
					shoot('r');
				}
	
			}



			break;




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
	_presentGame.clearMyDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	
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

	/*
	floorMesh.transformFloor.SetPosition(glm::vec3(movX, movY, -sbPos));
	floorMesh.transformFloor.SetRotation(glm::vec3(0, 0, 0));
	floorMesh.transformFloor.SetScale(glm::vec3(sbScale, sbScale, 1));
	shader.Update(floorMesh.transformFloor, camera1);
	//texture2.TexBind(0);
	floorMesh.form();
	
	transformNorthWall.SetPosition(glm::vec3(movX, sbPos + movY, 0));
	transformNorthWall.SetRotation(glm::vec3(0, 0, 0));
	transformNorthWall.SetScale(glm::vec3(sbScale, 1, sbScale));
	shader.Update(transformNorthWall, camera1);
	textureNw.TexBind(0);
	northwallMesh.form();

	transformSouthWall.SetPosition(glm::vec3(movX, movY - sbPos, 0));
	transformSouthWall.SetRotation(glm::vec3(0, 0, 0));
	transformSouthWall.SetScale(glm::vec3(sbScale, 1, sbScale));
	shader.Update(transformSouthWall, camera1);
	//textureNw.TexBind(0);
	southwallMesh.form();

	transformEastWall.SetPosition(glm::vec3(movX + sbPos, movY , 0));
	transformEastWall.SetRotation(glm::vec3(0, 0, 0));
	transformEastWall.SetScale(glm::vec3(1, sbScale, sbScale));
	shader.Update(transformEastWall, camera1);
	//textureNw.TexBind(0);
	eastwallMesh.form();

	transformWestWall.SetPosition(glm::vec3(movX - sbPos, movY, 0));
	transformWestWall.SetRotation(glm::vec3(0, 0, 0));
	transformWestWall.SetScale(glm::vec3(1, sbScale, sbScale));
	shader.Update(transformWestWall, camera1);
	//textureNw.TexBind(0);
	westwallMesh.form();
	*/
	
	
	shader.Update(eggMesh.transformEgg, camera1);
	texture3.TexBind(0);
	eggMesh.form();


	
				
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
	eggMesh.transformEgg.SetScale(glm::vec3(1, 1, 1));

	bulletMesh.updateSphere(*bulletMesh.transformBullet.GetPosition(), 1.0);
	eggMesh.updateSphere(*eggMesh.transformEgg.GetPosition(), 1.0);
	
}

