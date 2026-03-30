
#include "Object.h"
#include "Primitives.h"
#include <iostream>

// todo(jack): Abstract this? into a more structured global mesh thing? then the class just points to the mesh and texture it needs?
void Object::loadVertices(std::vector<float> vertices)
{
    std::cout << "Loading " << vertices.size() / 3 << " vertices" << std::endl;
     
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    // Check buffer data upload
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "Buffer data error: " << err << std::endl;
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // Release stuff so as to not have leaaaks
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Object::Object(Transform t)   
{
    renderTransform = t;
}

Object::~Object()
{
	glDeleteVertexArrays(1, &vaoID);
}

glm::vec3 Object::toGLM(QVector v)
{
    return glm::vec3(v.x, v.y, 0.0f);
}

void Object::syncPhysicsToRender()
{
    renderTransform.position.x = body->GetPosition().x * 1.0f / NDC_TO_PHYSICS_SCALE;// Other one had physics to NDC scale instead.
    renderTransform.position.y = body->GetPosition().y * 1.0f / NDC_TO_PHYSICS_SCALE;
    renderTransform.rotation.z = body->GetRotation(); // passed in actually already as radians
}

void Object::applyTransforms(ShaderProgram shader)
{
    glm::mat4 Model = glm::mat4(1.0f);
    glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    Model = glm::translate(Model, renderTransform.position);
    Model = glm::scale(Model, renderTransform.scale);
    Model = glm::rotate(Model, renderTransform.rotation.z, rotationAxis);
    shader.SetMatrix4("model", Model);
}

// todo(jack): Abstract this? into a more structured global texture thing? then the class just takes a texture string?
void Object::renderObject()
{
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textureID);
      glBindVertexArray(vaoID);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // we know generally that we are gonna be using a quad every time
      // Check for OpenGL errors after rendering
      GLenum err;
      while ((err = glGetError()) != GL_NO_ERROR) {
           std::cout << "OpenGL error in renderObject: " << err << std::endl;
      }
}

























