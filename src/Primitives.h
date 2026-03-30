#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <vector>
#include <cmath>

class Primitives {
public:
    // Get vertices as float arrays for OpenGL
    static std::vector<float> getQuadVertices();
    static std::vector<float> getQuadColorVertices();
    static std::vector<float> getQuadTexCoordVertices();
    
    static std::vector<float> getCubeVertices();
    static std::vector<float> getCubeColorVertices();
    static std::vector<float> getCubeTexCoordVertices();
    
    static std::vector<float> getTriangleVertices();
    static std::vector<float> getCircleVertices(int segments = 32);
    static std::vector<float> getSphereVertices(int latitudeSegments = 16, int longitudeSegments = 16);
    
    // Index buffers for reuse
    static std::vector<unsigned int> getQuadIndices();
    static std::vector<unsigned int> getCubeIndices();
};

#endif
