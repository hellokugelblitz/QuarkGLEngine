#include "Level.h"
#include "Platformer.h"
#include "InputManager.h"

Level::Level()
{
    //todo: im actually not even sure if this is needed herm
}

Level::Level(const std::string& filePath, QVector gravity)
{   
  //Create a physics world -- this is a our scene program, our applcation sends data from this straight to the render
  levelWorld=new QWorld(); 
  // Set the gravity value
  levelWorld->SetGravity(gravity); 
  //Set the iteration count per step of physics in the world.
  levelWorld->SetIterationCount(4);
  // Constructor that loads a level from file
  gamePhysicsObjects = {}; // todo: im sure if i actually have to do this?
  loadLevelFromFile(filePath);
}

Level::~Level()
{
    // Destructor
    for(PhysicsObject* obj : gamePhysicsObjects) {
        delete obj;
    }
    gamePhysicsObjects.clear();
}

void Level::loadLevelFromFile(const std::string& filePath)
{
    std::ifstream levelFile(filePath);
    // Check if the file was opened successfully
    if (!levelFile) 
    {
        std::cout << "Unable to open/read level file" << std::endl;
        return;
    }

    // Read the veretx file and write the characters to the corresponding string
    char ch;
    while (levelFile.get(ch)) {
        if(ch != '\n'){
            layout += ch;
        }
    }
    levelFile.close();
    std::cout << "Layout From Loaded File:\n" << layout << std::endl;
}

void Level::createPhysicsObject(float xPos, float yPos, float scale, bool isKinematic, const std::string& texture)
{
    // Create Transform 
    Transform objDimension;

    std::cout << "Adding block at: (" << xPos << ", " << yPos << ")\n";
    objDimension.position = glm::vec3(xPos, yPos, 0.0f);  // Near bottom
    objDimension.scale = glm::vec3(scale, scale, 1.0f);         

    // Create object
    PhysicsObject* newObj = new PhysicsObject(objDimension, texture); // Created on the heap
    if(isKinematic){
        newObj->getBody()->SetKinematicEnabled(true);
        newObj->getBody()->SetKinematicCollisionsEnabled(true);
    }
    gamePhysicsObjects.push_back(newObj);
}

void Level::createPlayerObj(float xPos, float yPos, float scale, bool isKinematic, const std::string& texture)
{
    // Create Transform 
    Transform playerDimension;

    std::cout << "Adding player at: (" << xPos << ", " << yPos << ")\n";
    playerDimension.position = glm::vec3(xPos, yPos, 0.0f);  // Near bottom
    playerDimension.scale = glm::vec3(scale, scale, 1.0f);         

    // Create object
    Platformer* newPlayer = new Platformer(playerDimension, texture); // 
    levelPlayers.push_back(newPlayer);
}

void Level::createLightObject(float xPos, float yPos, float scale, bool isKinematic, const std::string& texture)
{
    // Create Transform 
    Transform playerDimension;

    std::cout << "Adding player at: (" << xPos << ", " << yPos << ")\n";
    playerDimension.position = glm::vec3(xPos, yPos, 0.0f);  // Near bottom
    playerDimension.scale = glm::vec3(scale, scale, 1.0f);         

    // Create object
    Light* newLight = new Light(playerDimension, texture); // 
    levelLights.push_back(newLight);
}

void Level::setupLevel()
{
    // for char in levelstring
        //create a transform at that location
        //set the position and scale
        //set kinematics (if needed)
        //add the rigidbody to the world
    int columnNumber = LEVEL_SIZE;
    
    // Calculate grid dimensions
    int totalRows = layout.length() / columnNumber;
    float gridWidth = columnNumber * BLOCK_SIZE;
    float gridHeight = totalRows * BLOCK_SIZE;
    
    // Calculate offset to center the grid
    float startX = -gridWidth / 2.0f + BLOCK_SIZE / 2.0f;
    float startY = -gridHeight / 2.0f + BLOCK_SIZE / 2.0f;

    for (int i = 0; i<layout.length(); i++) {
        char c = layout[i];
        
        int row = i / columnNumber;
        int col = i % columnNumber;

        // Center the grid by adding the start offset
        float xPos = startX + (col * BLOCK_SIZE);
        float yPos = startY + (row * BLOCK_SIZE);        

        //std::cout << "Index " << i << ": char='" << c 
        //                  << "' (ASCII: " << (int)c << ")"
        //                  << ", row=" << row 
        //                  << ", col=" << col 
        //                  << ", pos=(" << xPos << ", " << yPos << ")" << std::endl;

        switch (c) {
            case '0':
                std::cout << "Skipping empty space...\n";
                break;
            case '1':
            {
                std::cout << "Block (kinematic on) " << row << std::endl;
                createPhysicsObject(xPos, yPos, BLOCK_SIZE, true, "../data/image/wall.png");
                break;
            }
            case '2':
            {
                std::cout << "Block (kinematic off)\n";
                createPhysicsObject(xPos, yPos, BLOCK_SIZE, false, "../data/image/wall.png");
                break;
            }
            case '3':
            {
                
                std::cout << "Creating Player\n";
                createPlayerObj(xPos, yPos, BLOCK_SIZE, false, "../data/image/dragon.png");
            }
            case '4':
            {
                std::cout << "Creating Light\n";
                createLightObject(xPos, yPos, BLOCK_SIZE, false, "../data/image/white.png");
            }
            default:
                std::cout << "Skipping empty space...\n";
                break;    
        };
    }

    std::cout << "Total gamePhysicsObjects created: " << gamePhysicsObjects.size() << std::endl;
    std::cout << "========== SETUP LEVEL END ==========" << std::endl;

    // for object in the scene
    for(PhysicsObject* obj : gamePhysicsObjects){
        std::cout << obj->getX() << std::endl;
        levelWorld->AddBody(obj->getBody());
    }
    for(Platformer* platformer : levelPlayers){
        levelWorld->AddBody(platformer->getBody());
    }
    for(Light* light : levelLights){
        levelWorld->AddBody(light->getBody());
    }
}

void Level::renderLevel(ShaderProgram program)
{
    for(PhysicsObject* obj : gamePhysicsObjects){
        obj->applyTransforms(program);
        obj->renderObject();
    }
    for(Platformer* platformer : levelPlayers){
        platformer->applyTransforms(program);
        platformer->renderObject();
    }
    for(Light* light : levelLights){
        light->applyTransforms(program);
        light->renderObject();
    }
}

void Level::clearLevel()
{
    // TODO: Clear the level layout
    layout.clear();
}

void Level::setLayout(const std::string& layout)
{
    // todo(jack): Set layout manually
}

// todo(jack): This has got to be the shittiest code ive ever written 
void Level::applyLevelForce(QVector forceVector)
{
    for(PhysicsObject* obj : gamePhysicsObjects){
        if(obj->getBody()->GetKinematicEnabled()){
            continue;
        }
        obj->getBody()->ApplyForce(forceVector);
    }
}

// Tells the physics engine to take the next step...
void Level::updateLevelPhysics()
{
    //Update the physics world
    levelWorld->Update();
}

void Level::syncPhysicsToRender()
{
    for(PhysicsObject* obj : gamePhysicsObjects){
        obj->syncPhysicsToRender();
    }
    // For every player in the world
    for(Platformer* platformer : levelPlayers){ 
        platformer->syncPhysicsToRender();
    }
    for(Light* light : levelLights){
        light->syncPhysicsToRender();
    }
}

void Level::handleInput(const InputManager& input) {
        
        // Handle level based stuff? creating objects and shit, mostly with mouse
        bool isMouseDown = input.isKeyDown(GLFW_MOUSE_BUTTON_RIGHT);

        // handling interactible objects like lights


        // Forward to player
        for (Platformer* player : levelPlayers) {
            player->handleInput(input);
        }
        for(Light* light : levelLights){
            light->handleInput(input);
        }

}

