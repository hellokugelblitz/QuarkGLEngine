
#ifndef PLAYER_H
#define PLAYER_H
#include "Object.h"
#include "InputManager.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <QuarkPhysics/qworld.h>
#include <QuarkPhysics/qbody.h>
#include <QuarkPhysics/qvector.h>
#include <QuarkPhysics/qcollision.h>
#include <QuarkPhysics/extensions/qplatformerbody.h>

class Platformer : public Object
{
	private:
		QPlatformerBody* platformerBody; // holds world space information for object (physics side)... 
		int playerID; // todo(jack): is there a better way to hold ids in c++?
		glm::vec3 playerVelocity;
	public:
		Platformer(Transform t, const std::string& texture);
		QPlatformerBody* getBody() { return static_cast<QPlatformerBody*>(body); }
		void handleInput(const InputManager& input);
};

#endif


