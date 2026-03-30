#ifndef LEVEL_H
#define LEVEL_H
#include "PhysicsObject.h"
#include "Platformer.h"
#include "Light.h"
#include "InputManager.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// todo: as always, get rid of uneeded things
#include <QuarkPhysics/qworld.h>
#include <QuarkPhysics/qbody.h>
#include <QuarkPhysics/qvector.h>
#include <QuarkPhysics/qcollision.h>

static const float BLOCK_SIZE = 0.1f;
static const int LEVEL_SIZE = 20;

class Level
{
	private:	
		std::string layout;
		std::vector<PhysicsObject*> gamePhysicsObjects; // holding pointers to the game objects...
		std::vector<Platformer*> levelPlayers; // holds the player object!
		std::vector<Light*> levelLights;
		QWorld* levelWorld; // the level owns the hirarchy i guess
		void loadLevelFromFile(const std::string& filePath);
		void createPhysicsObject(float xPos, float yPos, float scale, bool isKinematic, const std::string& texture);
		void createPlayerObj(float xPos, float yPos, float scale, bool isKinematic, const std::string& texture);
		void createLightObject(float xPos, float yPos, float scale, bool isKinematic, const std::string& texture);
	public:
		Level();
		Level(const std::string& filePath, QVector gravity); // overloaded constructor automatically loads level from file, no need to expose elswhere
		~Level();
		
		void setupLevel();
		void renderLevel(ShaderProgram program);
		void clearLevel();
		void setLayout(const std::string& layout);
		void applyLevelForce(QVector forceVector);
		void updateLevelPhysics();
		void syncPhysicsToRender(); 

		void handleInput(const InputManager& input);
};

#endif


/*
Standard level -- nothing in it

0000000000
0000000000
0000000000
0010000100
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000

1 = static block
2 = physics block
3 = connected static block
4 = connected physics block

*/


