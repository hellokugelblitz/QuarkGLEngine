#ifndef LIGHT_H
#define LIGHT_H
#include "InputManager.h"
#include "Engine.h"
#include "Shader.h"
#include "Object.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <QuarkPhysics/qworld.h>
#include <QuarkPhysics/qbody.h>
#include <QuarkPhysics/qvector.h>
#include <QuarkPhysics/qcollision.h>

class Light : public Object
{
	private:
		QRigidBody* rigidBody;
	public:
		Light(Transform t, const std::string& path);
		Light(const Light&) = delete;
		Light& operator=(const Light&) = delete;
		QRigidBody* getBody() { return static_cast<QRigidBody*>(body); }
		void handleInput(const InputManager& input);

};

#endif

