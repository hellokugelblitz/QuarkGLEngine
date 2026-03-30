#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// CONSTRUCTOR
ShaderProgram::ShaderProgram(const std::string& vPath, const std::string& fPath)
{
	//set our shader paths
  vShader.shaderPath = vPath;
  fShader.shaderPath = fPath;

	//Create the shader program
	shaderProgram = glCreateProgram(); // will fill our ID.
  
  // this will fill in our struct with the id we need...
  loadShaderFiles(vShader.shaderPath, fShader.shaderPath); 
  
  // compiles both the vertex and fragment shaders...
  compileShaders();

  // links both vertex and fragment shaders...
  linkShaders();
}

ShaderProgram::~ShaderProgram()
{
  if(shaderProgram)
  {
    glDeleteProgram(shaderProgram);
  }
}

// PRIVATE

void ShaderProgram::compileShaders()
{
  // will be used to tell us if there is an error in our shader compile.
  GLint compileStatus; 
  char* errorMessage[256]; 

  // Set up the shader
  vShader.shaderID = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vCharSource = vShader.shaderString.c_str(); // source expects a char*
  glShaderSource(vShader.shaderID, 1, &vCharSource, NULL);
  glCompileShader(vShader.shaderID); // compile the vertex shader

  // check compile errors for the vertex shader
  glGetShaderiv(vShader.shaderID, GL_COMPILE_STATUS, &compileStatus);
  if (compileStatus != GL_TRUE)
  {
     GLsizei log_length = 0;
     GLchar message[1024];
     glGetShaderInfoLog(vShader.shaderID, 1024, &log_length, message);
     std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << message << std::endl;
  }
  else 
  {
   std::cout << " + Vertex Shader Compiled" << std::endl;
  }
  
  // Set up the shader
  fShader.shaderID = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fCharSource = fShader.shaderString.c_str(); // source expects a char*
  glShaderSource(fShader.shaderID, 1, &fCharSource, NULL);
  glCompileShader(fShader.shaderID);

  // Compile Error Check
  glGetShaderiv(fShader.shaderID, GL_COMPILE_STATUS, &compileStatus);
  if (compileStatus != GL_TRUE)
  {
     GLsizei log_length = 0;
     GLchar message[1024];
     glGetShaderInfoLog(fShader.shaderID, 1024, &log_length, message);
     std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << message << std::endl;
  }
  else 
  {
   std::cout << " + Fragment Shader Compiled" << std::endl;
  }
  std::cout << "Shaders Compiled!" << std::endl;
}

void ShaderProgram::linkShaders()
{
    std::cout << "Linking Shaders..." << std::endl;
    // Attaches and links the shader
    glAttachShader(shaderProgram, vShader.shaderID);
    glAttachShader(shaderProgram, fShader.shaderID);
    glLinkProgram(shaderProgram);
    std::cout << "Shaders Linked!" << std::endl; 
}

void ShaderProgram::loadShaderFiles(const std::string& vPath, const std::string& fPath)
{

    std::cout << "Reading Shader Files..." << std::endl; 
    std::ifstream vertexFile(vPath);
    std::ifstream fragmentFile(fPath);

    // Check if the file was opened successfully
    if (!vertexFile) 
    {
        std::cout << "Unable to open vertex file" << std::endl;
        return;
    } 
    else if (!fragmentFile) 
    {
        std::cout << "Unable to open fragment file" << std::endl;
        return; 
    }

    std::cout << "Read shader files!" << std::endl;

    // Read the veretx file and write the characters to the corresponding string
    char ch;
    while (vertexFile.get(ch)) {
        vShader.shaderString += ch;
    }
    vShader.shaderString += '\n';
    vertexFile.close();

    while(fragmentFile.get(ch)) {
      fShader.shaderString += ch;
    }
    fShader.shaderString += '\n';
    fragmentFile.close();
}

// PUBLIC

void ShaderProgram::useProgram()
{
    glUseProgram(shaderProgram);
}

GLuint ShaderProgram::getShaderProgram()
{
    return shaderProgram;
}

// Matrix functions

// we use this to set the model matrix for a given vertex
void ShaderProgram::SetMatrix4 (const std::string& name, const glm::mat4 mat)
{
  // first we need to grab the location of the uniform value
  GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
  //Then we can set it
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}
