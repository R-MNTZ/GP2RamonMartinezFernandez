#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct MainCamera
{
public:
	MainCamera()
	{
	}

	void startMainCamera(const glm::vec3& position, float fov, float aspect, float nearClip, float farClip)
	{
		this->position = position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = glm::cross(up, forward);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetVP() const
	{
		return projection * glm::lookAt(position, position + forward, up);
	}

	void MoveForward(float stepLength)
	{
		position += forward * stepLength;
	}

	void MoveBackwards(float stepLength)
	{
		position -= forward * stepLength;
	}

	void MoveUp(float stepLength)
	{
		position += up * stepLength;
	}

	void MoveDown(float stepLength)
	{
		position -= up * stepLength;
	}


	void MoveRight(float stepLength)
	{
		position += right * stepLength;
	}

	void MoveLeft(float stepLength)
	{
		position -= right * stepLength;
	}

	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	//void RotateY(float angle)
	//{
	//	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	//	glm::mat4 rotation = glm::rotate(angle, UP);

	//	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	//	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	//}

protected:
private:
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
};


