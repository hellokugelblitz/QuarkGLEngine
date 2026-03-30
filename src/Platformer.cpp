#include "Object.h"
#include "Platformer.h"
#include "Primitives.h"
#include <iostream>

// In Platformer constructor
Platformer::Platformer(Transform t, const std::string& path) : Object(t)
{
    // Setting our render & physics side instances.
    renderTransform = t;
    textureID = TextureCache::load(path);
    
    platformerBody = new QPlatformerBody();
    body = platformerBody;

    platformerBody->SetGravity(QVector(0.0f, -0.98f)); // todo: get rid of random stuff like this...

    // Set walking speed and acceleration
    platformerBody->SetWalkSpeed(60.0f);           // Base movement speed
    platformerBody->SetWalkAcelerationRate(0.2f); // How fast to reach max speed
    platformerBody->SetWalkDecelerationRate(0.2f); // How fast to stop
    // Add these after creating the platformerBody
    platformerBody->SetMass(1.0f);
    platformerBody->SetFriction(0.0f);
    //platformerBody->SetRestitution(0.1f);	
    platformerBody->SetJumpDurationFrameCount(15);
    // Jump shit
    platformerBody->SetJumpFallGravityMultiplier(2.0f);
    platformerBody->SetJumpGravityMultiplier(0.8f);
    platformerBody->SetMaxJumpCount(1);

    // Set floor angle limits (prevent walking up too steep slopes)
    platformerBody->SetFloorMaxAngleDegree(60.0f);
    platformerBody->SetMovingFloorSnapOffset(5.0f); // Snap to moving floors within 5 units

    // Geometry
    float physicsWidth = renderTransform.scale.x * NDC_TO_PHYSICS_SCALE;
    float physicsHeight = renderTransform.scale.y * NDC_TO_PHYSICS_SCALE;
    mesh = QMesh::CreateWithRect(QVector(physicsWidth,physicsHeight),QVector(0.0f, 0.0f));
    platformerBody->AddMesh(mesh); 
    
    // Position
    float physicsPositionX = renderTransform.position.x * NDC_TO_PHYSICS_SCALE; 
    float physicsPositionY = renderTransform.position.y * NDC_TO_PHYSICS_SCALE;
    platformerBody->SetPosition(QVector(physicsPositionX, physicsPositionY));
	
    // Rotation
    float physicsRotationZ = renderTransform.rotation.z * NDC_TO_PHYSICS_SCALE;
    platformerBody->SetRotation(physicsRotationZ,true); // grabbing the angle in the z axis?

    loadVertices(Primitives::getQuadTexCoordVertices());
}

void Platformer::handleInput(const InputManager& input)
{
    int side = input.getHorizontalAxis();
    platformerBody->Walk(side);
    
    // Track jump button state (this is fine - it's input tracking, not physics state)
    static bool wasSpaceDown = false;
    bool isSpaceDown = input.isKeyDown(GLFW_KEY_UP); // todo: this wouldnt be platform independent.
    
    if (isSpaceDown && !wasSpaceDown) {
        std::cout << "Jump pressed - on floor: " << platformerBody->GetIsOnFloor() << std::endl;
        platformerBody->Jump(25.0f, true);  // Use unconditional for now
        
        // Check velocity to see if jump applied
        QVector vel = platformerBody->GetControllerVerticalVelocity();
        std::cout << "Velocity after jump: (" << vel.x << ", " << vel.y << ")" << std::endl;
    }
    
    if (!isSpaceDown && wasSpaceDown) {
        std::cout << "Jump released" << std::endl;
        platformerBody->ReleaseJump();
    }
    
    wasSpaceDown = isSpaceDown;
}
