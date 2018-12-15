#include "MyMesh.h"
#include "GameScene.h"
#include <vector>




void MyMesh::init(VertStruct* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	
	

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	startModel(model);
	
}

void MyMesh::startModel(const IndexedModel& model)
{

	counterDraw = model.indices.size();

	glGenVertexArrays(1, &vertexArrayObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(vertexArrayObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO
	Sphere sphere1;
}

MyMesh::MyMesh()
{
	counterDraw = NULL;
}

void MyMesh::prepareModel(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	startModel(model);
}

MyMesh::~MyMesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays
}

void MyMesh::form()
{
	glBindVertexArray(vertexArrayObject);
	
	glDrawElements(GL_TRIANGLES, counterDraw, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, counterDraw);
	
	glBindVertexArray(0);
}

void MyMesh::updateSphere(glm::vec3 pos, float r)
{
	meshSphere.SetPosition(pos);
	meshSphere.SetRadius(r);
	
}

void MyMesh::updateTransform1() {
	GameScene gs;
	transformMonkey.SetPosition(glm::vec3(gs.movX, gs.movY, 0));
	transformMonkey.SetRotation(glm::vec3(gs.rotX, gs.rotY, gs.rotZ));
	transformMonkey.SetScale(glm::vec3(1, 1, 1));

	transformBullet.SetPosition(glm::vec3(gs.initialBulletPosx, gs.initialBulletPosy, 0));
	transformBullet.SetRotation(glm::vec3(0, 0, 0));
	transformBullet.SetScale(glm::vec3(0.1, 0.1, 0.1));

	transformCeiling.SetPosition(glm::vec3(0, 0, gs.sbPos));
	transformCeiling.SetRotation(glm::vec3(0, 0, 0));
	transformCeiling.SetScale(glm::vec3(gs.sbScale, gs.sbScale, 1));

	transformEgg.SetPosition(glm::vec3(gs.eggX, 0, 0));
	transformEgg.SetRotation(glm::vec3(0, 0, 0));
	transformEgg.SetScale(glm::vec3(1, 1, 1));
}

