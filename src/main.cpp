#include "Engine.h"
#include "PhysicsObject.h"
#include "Shader.h"
#include "Level.h"
#include "TextureCache.h"
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <QuarkPhysics/qworld.h>
#include <QuarkPhysics/qbody.h>
#include <QuarkPhysics/qvector.h>
#include <QuarkPhysics/qcollision.h>

// Game Globals
static const QVector ZERO_GRAVITY = QVector(0.0f,0.0f);
static const std::string VERTEX_SHADER_FILE = "../shaders/vertex.glsl";
static const std::string FRAGMENT_SHADER_FILE = "../shaders/fragment.glsl";
static const std::string LEVEL_ONE_FILE = "../data/level3.txt";

// GLFW callbacks
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Some stuff we want to handle directly here, like wirframe in debug mode and closing the app
    switch (key) 
    { 
      case GLFW_KEY_ESCAPE: 
      {
          glfwSetWindowShouldClose(Engine::gameWindow, GLFW_TRUE); 
          break; 
      } 

      case GLFW_KEY_GRAVE_ACCENT:
      {
          if(action == GLFW_PRESS){
            if(Engine::wireframeModeActivated){
              Engine::wireframeModeActivated = false;
            } else {
              Engine::wireframeModeActivated = true;
            }
          }
          break;
      }

      default: 
        // Some other key is being pressed, handle it in the inputManager
        InputManager::getInstance().keyCallback(key, scancode, action, mods);
        break; 
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  // Passing cursor position handling off to the input manager
  InputManager::getInstance().cursorPositionCallback(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  InputManager::getInstance().mouseButtonCallback(button, action, mods);
}

void createGLFWWindow()
{
  if(glfwInit() != GL_TRUE){
    std::cout << "Error creating glfwWindow" << std::endl;
    return; // return out of the function
  }

  // this is the basic chunk of code that allows us to open a window that can be interacted with in glfw....
  // Not strictly speaking necessary but I need to set the version of GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // I need to tell it to double buffer
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  
  // I need to tell glfw that the window should be resizable
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // we need to tell glfw to use GL to redraw the framebuffer
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Window i GLFW comes with a framebuffer already attached?
  Engine::gameWindow = glfwCreateWindow(Engine::GAME_WIDTH, Engine::GAME_HEIGHT, Engine::GAME_TITLE, 0, 0); 
  glfwMakeContextCurrent(Engine::gameWindow);

  //setting out callbacks
  glfwSetKeyCallback(Engine::gameWindow, key_callback); 
  glfwSetCursorPosCallback(Engine::gameWindow, cursor_position_callback);
  glfwSetMouseButtonCallback(Engine::gameWindow, mouse_button_callback);

  int bufferWidth, bufferHeight;
  glfwGetFramebufferSize(Engine::gameWindow, &bufferWidth, &bufferHeight);

  // load glad with this function I will never remember
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return;
  }

  glDisable(GL_DEPTH_TEST);
  glViewport(0,0,bufferWidth, bufferHeight);
}

void runGame()
{
  ShaderProgram program = ShaderProgram(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
  Level levelOne(LEVEL_ONE_FILE, QVector(0.0f,-0.5f));
  levelOne.setupLevel();

  /*
    Ideal Logic at some point:

    Begin Frame
    Do Pre-Physics gameplay logic
    Send object locations to physics engine
    Simulate Physics via the physics engine
    Update to new object locations from physics engine
    Do Post-Physics gameplay logic
    Packaged/send all final object locations to the renderer
    Renderer processes objects, then sends the results to GPU
    GPU does what the renderer says and produces the final image
    Frame Ends
  */

  //Add the Rigid Body to the World
  double accumulator = 0.0;
  const double fixedStep = 1.0 / 120.0; // todo: magic number
  double oldTimeSinceStart = 0.0; // used for deltatime.
  while(!glfwWindowShouldClose(Engine::gameWindow))
  {
    InputManager::getInstance().beginFrame(); 
    glfwPollEvents(); 
    
    //wireframeMode stuff
    if(Engine::wireframeModeActivated){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //delta time stuff
    double timeSinceStart = glfwGetTime();
    Engine::deltaTime = timeSinceStart - oldTimeSinceStart; // Deltatime helps us keep track of the tme elapsed between two frame updates.
    oldTimeSinceStart = timeSinceStart; 
    accumulator += Engine::deltaTime;

    // Handle input before physics (because google AI said it was okay)
    levelOne.handleInput(InputManager::getInstance());
    
    // updates the phyiscs simulation at 60hz only... this doesnt send physics information to the renderer
    while(accumulator >= fixedStep){
      levelOne.updateLevelPhysics();
      levelOne.syncPhysicsToRender();
      accumulator -= fixedStep;
    }
    
    glClearColor(0.184314f,0.184314f,0.309804f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // Then we actually render..
    //std::cout << "Game Time: " << timeSinceStart << std::endl;
    program.useProgram(); 
    levelOne.renderLevel(program); // todo(jack): dont pass the shader program in like this. 
    
    glfwSwapBuffers(Engine::gameWindow); 
    // todo: make this make sense MAKE IT MAKE SENSE
  }
  glfwDestroyWindow(Engine::gameWindow);
  glfwTerminate();
}

int main()
{
  createGLFWWindow();
  runGame();
  std::cout << "Exiting Program..." << std::endl;
  return 0;
}
