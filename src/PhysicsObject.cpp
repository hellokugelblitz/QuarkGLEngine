#include "Object.h"
#include "PhysicsObject.h"
#include "Primitives.h"
#include <iostream>

// In Object constructor
PhysicsObject::PhysicsObject(Transform t, const std::string& path) : Object(t)
{
    // Setting our render & physics side instances.
    renderTransform = t;
    textureID = TextureCache::load(path); 

    rigidBody = new QRigidBody();
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
