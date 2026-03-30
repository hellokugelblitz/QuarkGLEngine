#include "Object.h"
#include "Light.h"
#include "Primitives.h"
#include <iostream>

// In Object constructor
Light::Light(Transform t, const std::string& path) : Object(t)
{
    // Setting our render & physics side instances.
    renderTransform = t;
    textureID = TextureCache::load(path); 

    rigidBody = new QRigidBody();
    rigidBody->SetKinematicEnabled(GL_TRUE);
    body = rigidBody;
    // Geometry
    float physicsWidth = renderTransform.scale.x * NDC_TO_PHYSICS_SCALE;
    float physicsHeight = renderTransform.scale.y * NDC_TO_PHYSICS_SCALE;
    mesh = QMesh::CreateWithRect(QVector(physicsWidth,physicsHeight),QVector(0.0f, 0.0f));
    rigidBody->AddMesh(mesh); 
    
    // Position
    float physicsPositionX = renderTransform.position.x * NDC_TO_PHYSICS_SCALE; 
    float physicsPositionY = renderTransform.position.y * NDC_TO_PHYSICS_SCALE;
    rigidBody->SetPosition(QVector(physicsPositionX, physicsPositionY));
	
    // Rotation
    float physicsRotationZ = renderTransform.rotation.z * NDC_TO_PHYSICS_SCALE;
    rigidBody->SetRotation(physicsRotationZ,true); // grabbing the angle in the z axis? todo:
    
    loadVertices(Primitives::getQuadTexCoordVertices());
}

void Light::handleInput(const InputManager& input)
{
    int leftSide   = (getX() + 1) * (Engine::GAME_WIDTH  / 2) - ((Engine::NDC_BLOCK_SIZE * Engine::GAME_WIDTH)  / 4);
    int rightSide  = (getX() + 1) * (Engine::GAME_WIDTH  / 2) + ((Engine::NDC_BLOCK_SIZE * Engine::GAME_WIDTH)  / 4);
    int topSide    = (getY() + 1) * (Engine::GAME_HEIGHT / 2) + ((Engine::NDC_BLOCK_SIZE * Engine::GAME_HEIGHT) / 4);
    int bottomSide = (getY() + 1) * (Engine::GAME_HEIGHT / 2) - ((Engine::NDC_BLOCK_SIZE * Engine::GAME_HEIGHT) / 4);
   
    // todo(jack): fix the fast drag issue
    bool dragging = false;
    if(dragging || (input.getMouseX() >= leftSide && input.getMouseX() <= rightSide && input.getMouseY() >= bottomSide && input.getMouseY() <= topSide))
    {
        static int mouseXStart = 0;
        static int mouseYStart = 0;

        if(input.wasKeyPressed(GLFW_MOUSE_BUTTON_LEFT)){
            mouseXStart = input.getMouseX();
            mouseYStart = input.getMouseY();
        }
        if(input.isKeyDown(GLFW_MOUSE_BUTTON_LEFT)){
            dragging = true;
            float deltaX = (input.getMouseX() - mouseXStart) * (2.0f / Engine::GAME_WIDTH) * NDC_TO_PHYSICS_SCALE;
            float deltaY = (input.getMouseY() - mouseYStart) * (2.0f / Engine::GAME_HEIGHT) * NDC_TO_PHYSICS_SCALE;

            QVector currentPos = body->GetPosition();
            body->SetPosition(QVector(currentPos.x + deltaX, currentPos.y + deltaY));

            QVector newPos = body->GetPosition();
            mouseXStart = input.getMouseX();
            mouseYStart = input.getMouseY();
        }
      if(input.wasKeyReleased(GLFW_MOUSE_BUTTON_LEFT)){
            dragging = false;
      }
    }
}
