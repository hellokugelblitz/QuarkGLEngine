#ifndef OBJECT_H
#define OBJECT_H
#include "Shader.h"
#include "TextureCache.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <QuarkPhysics/qworld.h>
#include <QuarkPhysics/qbody.h>
#include <QuarkPhysics/qvector.h>
#include <QuarkPhysics/qcollision.h>

const float PHYSICS_TO_RENDER_SCALE = 0.0001f;
const float NDC_TO_PHYSICS_SCALE = 10000.0f;
const float PHYSICS_TO_NDC_SCALE = 1.0f / NDC_TO_PHYSICS_SCALE;

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation; // given in radians FYI
    glm::vec3 scale;

    Transform(
        glm::vec3 pos = glm::vec3(0.0f),
        glm::vec3 rot = glm::vec3(0.0f),
        glm::vec3 scl = glm::vec3(1.0f)
    )
        : position(pos), rotation(rot), scale(scl) {}
};

class Object
{
	protected: // todo(jack): can some of these members be private?
		Transform renderTransform; // world space 
		QBody* body;
		QMesh* mesh;
		GLuint vaoID; 
		GLuint vboID;
		GLuint textureID;
		void loadVertices(std::vector<float> vertices);
	public:
		Object(Transform t);
		~Object();

		// Delete copy constructor and 
		Object(const Object&) = delete;
    		Object& operator=(const Object&) = delete;
		
		// static member function to translate Physics vectors to glm...
		static glm::vec3 toGLM(QVector v); 

		// Graphics and Rendering
		void syncPhysicsToRender();	
		void renderObject();
		void applyTransforms(ShaderProgram shader);
	
		// Getters
		float getX() const { return renderTransform.position.x; }
		float getY() const { return renderTransform.position.y; }
		QBody* getBody() { return body; }
		QMesh* getMesh() { return mesh; }
};

#endif

