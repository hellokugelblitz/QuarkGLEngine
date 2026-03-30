#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H
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

class PhysicsObject : public Object
{
	private:
		QRigidBody* rigidBody;
	public:
		PhysicsObject(Transform t, const std::string& path);
		PhysicsObject(const PhysicsObject&) = delete;
		PhysicsObject& operator=(const PhysicsObject&) = delete;
		QRigidBody* getBody() { return static_cast<QRigidBody*>(body); }
};

#endif

