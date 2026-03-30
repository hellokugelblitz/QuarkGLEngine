#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H
#include "stb_image.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class TextureCache
{
    public:
        static GLuint load(const std::string& path);
        static GLuint get(const std::string& path)
        {
            auto it = cache.find(path);
            if (it != cache.end()) return it->second;
            return 0; 
        }
    private:
        static std::unordered_map<std::string, GLuint> cache;
};
#endif
