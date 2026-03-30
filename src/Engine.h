#ifndef ENGINE_H
#define ENGINE_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
    inline int GAME_WIDTH = 600;
    inline int GAME_HEIGHT = 600;
    inline float NDC_BLOCK_SIZE = 0.1f; // dont think i should do this but whatever
    inline const char* GAME_TITLE = "SimpleEngine";
    inline double deltaTime = 0.0f;
    inline bool wireframeModeActivated = false;
    inline GLFWwindow* gameWindow = nullptr;
}

// todo(jack): Create some kind of static BOOT UP?


#endif
