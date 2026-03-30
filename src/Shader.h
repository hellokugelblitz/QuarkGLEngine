// This class will be responsible for compiling and linking the shaders in our program....
#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct 
{
	std::string shaderPath;
	std::string shaderString;
	GLuint shaderID;
} Shader;

class ShaderProgram 
{
	private:
		GLuint shaderProgram;
		Shader vShader;
		Shader fShader;
		
		void compileShaders(); // Compiele shaders
		void linkShaders();
		void loadShaderFiles(const std::string& vPath, const std::string& fPath); // loads shader files or string inputs (parsing done seperatley)
	public:
		ShaderProgram(const std::string& vPath, const std::string& fPath);
		~ShaderProgram(); // destroys the shader program
	
		void useProgram(); // register and assign IDs
		GLuint getShaderProgram();
		void SetMatrix4 (const std::string& name, const glm::mat4 mat);
		void setTexture ();
};

#endif

