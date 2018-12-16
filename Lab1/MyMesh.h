#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "transform.h"


struct VertStruct
{
public:
	VertStruct(const glm::vec3& position, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &position; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Sphere
{
public:
	glm::vec3 position;
	float radius;
	Sphere() {}
	Sphere(glm::vec3 position, float radius) {
	
	}


	glm::vec3 GetPos() { return position; }
	float GetRad() { return radius; }

	void SetPosition(glm::vec3& position) { this->position = position; } 
	void SetRadius(float& radius) { this->radius = radius; }

};


class MyMesh
{
public:
	MyMesh();
	~MyMesh();
	Sphere meshSphere;

	TransformStruct transformMonkey;
	TransformStruct transformCeiling;
	TransformStruct transformFloor;
	TransformStruct transformNorthWall;
	TransformStruct transformSouthWall;
	TransformStruct transformEastWall;
	TransformStruct transformWestWall;
	TransformStruct transformEgg;
	TransformStruct transformBullet;
	

	void form();
	void updateSphere(glm::vec3 pos, float r);
	void updateTransform1();
	void initThis(VertStruct* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void prepareModel(const std::string& filename);
	void startModel(const IndexedModel& model);

	glm::vec3 getSpherePos() { return meshSphere.GetPos(); }
	float getSphereRad() { return meshSphere.GetRad(); }

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int counterDraw; //how much of the vertexArrayObject do we want to form
};



