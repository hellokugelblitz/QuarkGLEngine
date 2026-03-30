#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Engine.h"
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <unordered_set>

class InputManager {
    public:
        static InputManager& getInstance() {
            static InputManager instance;
            return instance;
        }
        
        void keyCallback(int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS) {
                keyStates[key] = true;
                pressedKeys.insert(key);
            } else if (action == GLFW_RELEASE) {
                keyStates[key] = false;
                releasedKeys.insert(key);
            }
        }

        void cursorPositionCallback(double xpos, double ypos){
            lastMousePosX = mousePosX;
            lastMousePosY = mousePosY;
            mousePosX = xpos;
            mousePosY = ypos;
        }
 
        void mouseButtonCallback(int button, int action, int mods){
            // Dont see why we cant just add this to the same keys?? todo(jack): at some point create a mouse 
            // specific thing "key" for mouse buttons doesnt sound/feel right...
            if (action == GLFW_PRESS) {
                keyStates[button] = true;
                pressedKeys.insert(button);
            } else if (action == GLFW_RELEASE) {
                keyStates[button] = false;
                releasedKeys.insert(button);
            }
        }

        void beginFrame() {
            pressedKeys.clear();
            releasedKeys.clear();
        }
        
        bool isKeyDown(int key) const {
            auto it = keyStates.find(key);
            return it != keyStates.end() && it->second;
        }
        
        bool wasKeyPressed(int key) const {
            return pressedKeys.count(key) > 0;
        }
        
        bool wasKeyReleased(int key) const {
            return releasedKeys.count(key) > 0;
        }
        
        int getHorizontalAxis() const {
            int axis = 0;
            if (isKeyDown(GLFW_KEY_A) || isKeyDown(GLFW_KEY_LEFT)) axis += 1;
            if (isKeyDown(GLFW_KEY_D) || isKeyDown(GLFW_KEY_RIGHT)) axis -= 1;
            return axis;
        }

        int getMouseX() const {
            return mousePosX;
        }
        int getMouseY() const {
            return Engine::GAME_HEIGHT - mousePosY; // Okay, so we need to flip Y since glfw and openGL work differently and the rest of program expects it this way....
        }
        
    private:
        InputManager() = default;
        
        std::unordered_map<int, bool> keyStates;      // Current state of all keys
        std::unordered_set<int> pressedKeys;          // Keys pressed THIS frame
        std::unordered_set<int> releasedKeys;         // Keys released THIS frame
        double mousePosX;
        double mousePosY;
        double lastMousePosX;
        double lastMousePosY;
    };

#endif
