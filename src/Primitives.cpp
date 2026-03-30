#include "Primitives.h"
#include <cmath>
#include <vector>

// Utility functions written by AI....

    std::vector<float> Primitives::getQuadVertices() {
        return {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f,  
        -0.5f,  0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f,  
    };
}

std::vector<float> Primitives::getQuadColorVertices() {
    return {
        // positions           // colors (RGB)
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  // bottom-left red
         0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  // bottom-right green
        -0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  // top-left blue
         0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f   // top-right yellow
    };
}

std::vector<float> Primitives::getQuadTexCoordVertices() {
    return {
        // positions           // texture coords (u, v)
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, 0.0f,    1.0f, 0.0f,  // bottom-right
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f,  // top-left
         0.5f,  0.5f, 0.0f,    1.0f, 1.0f   // top-right
    };
}

std::vector<unsigned int> Primitives::getQuadIndices() {
    return {
        0, 1, 2,  // first triangle
        1, 3, 2   // second triangle
    };
}

std::vector<float> Primitives::getCubeVertices() {
    return {
        // front face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        
        // back face
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f
    };
}

std::vector<unsigned int> Primitives::getCubeIndices() {
    return {
        // front face
        0, 1, 2,  1, 3, 2,
        // back face
        4, 6, 5,  5, 6, 7,
        // left face
        0, 2, 4,  4, 2, 6,
        // right face
        1, 5, 3,  3, 5, 7,
        // bottom face
        0, 4, 1,  1, 4, 5,
        // top face
        2, 3, 6,  3, 7, 6
    };
}

std::vector<float> Primitives::getTriangleVertices() {
    return {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
}

std::vector<float> Primitives::getCircleVertices(int segments) {
    std::vector<float> vertices;
    float radius = 0.5f;
    
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        vertices.push_back(radius * cos(angle));
        vertices.push_back(radius * sin(angle));
        vertices.push_back(0.0f);
    }
    
    return vertices;
}
