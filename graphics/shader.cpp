#include "shader.h"
#include "../src/log.h"
#include <cstdint>
#include <glad/glad.h>
#include <string>
#include "helpers.h"

namespace eclipse::graphics {

shader::shader(const std::string &vertex, const std::string &fragment) {

  mProgramId = glCreateProgram(); ECLIPSE_CHECK_GL_ERROR;
  char errorLog[512]; 
  int status = GL_FALSE;  

  uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);ECLIPSE_CHECK_GL_ERROR;

  {
    const GLchar *glSource = vertex.c_str();ECLIPSE_CHECK_GL_ERROR;
    glShaderSource(vertexShaderId, 1, &glSource, NULL);ECLIPSE_CHECK_GL_ERROR;
    glCompileShader(vertexShaderId);ECLIPSE_CHECK_GL_ERROR;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status);ECLIPSE_CHECK_GL_ERROR;
    if (status != GL_TRUE) {
      glGetShaderInfoLog(vertexShaderId, sizeof(errorLog), NULL, errorLog);ECLIPSE_CHECK_GL_ERROR;

      ECLIPSE_ERROR("Error Compiling Vertex Shaders {}",errorLog);
    } else {
      glAttachShader(mProgramId, vertexShaderId);ECLIPSE_CHECK_GL_ERROR;
    }
  }

  uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);ECLIPSE_CHECK_GL_ERROR;

  if (status == GL_TRUE)

  {
    const GLchar *glSource = fragment.c_str();ECLIPSE_CHECK_GL_ERROR;
    glShaderSource(fragmentShaderId, 1, &glSource, NULL);ECLIPSE_CHECK_GL_ERROR;
    glCompileShader(fragmentShaderId);ECLIPSE_CHECK_GL_ERROR;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status);ECLIPSE_CHECK_GL_ERROR;
    if (status != GL_TRUE) {
      glGetShaderInfoLog(fragmentShaderId, sizeof(errorLog), NULL, errorLog);ECLIPSE_CHECK_GL_ERROR;
      ECLIPSE_ERROR("Error Compiling Framgent Shaders {}",errorLog);ECLIPSE_CHECK_GL_ERROR;
    } else {
      glAttachShader(mProgramId, fragmentShaderId);ECLIPSE_CHECK_GL_ERROR;
    }
  }

ECLIPSE_ASSERT(status == GL_TRUE, "Error compiling shader");

if(status == GL_TRUE){
  glLinkProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
  glValidateProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
  glGetProgramiv(mProgramId,GL_LINK_STATUS,&status);ECLIPSE_CHECK_GL_ERROR;
  if(status != GL_TRUE){
    glGetProgramInfoLog(mProgramId,sizeof(errorLog),NULL,errorLog);ECLIPSE_CHECK_GL_ERROR;
    ECLIPSE_ERROR("Error linking shaders {}",errorLog);
    mProgramId = -1;ECLIPSE_CHECK_GL_ERROR;
  }
 
}

glDeleteShader(vertexShaderId);ECLIPSE_CHECK_GL_ERROR;
glDeleteShader(fragmentShaderId);ECLIPSE_CHECK_GL_ERROR;
  
}


void shader::Bind(){
  glUseProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
}

void shader::Unbind(){
  glUseProgram(0);ECLIPSE_CHECK_GL_ERROR;
}

shader::~shader(){
  glUseProgram(0);ECLIPSE_CHECK_GL_ERROR;
  glDeleteProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
}



void shader::SetUniformInt(const std::string& name, int val){
  glUseProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
  glUniform1i(GetUniformLocations(name),val);ECLIPSE_CHECK_GL_ERROR;
}
void shader::SetUniformFloat(const std::string& name, float val){
  
  glUseProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
  glUniform1f(GetUniformLocations(name),val);ECLIPSE_CHECK_GL_ERROR;
}
void shader::SetUniformFloat2(const std::string& name, float val1, float val2){
  
  glUseProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
  glUniform2f(GetUniformLocations(name),val1, val2);ECLIPSE_CHECK_GL_ERROR;
}
void shader::SetUniformFloat3(const std::string& name, float val1, float val2, float val3){
  
  glUseProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
  glUniform3f(GetUniformLocations(name),val1,val2,val3);ECLIPSE_CHECK_GL_ERROR;
}
void shader::SetUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4){
  
  glUseProgram(mProgramId);ECLIPSE_CHECK_GL_ERROR;
  glUniform4f(GetUniformLocations(name),val1,val2,val3,val4);ECLIPSE_CHECK_GL_ERROR;
}




int shader::GetUniformLocations(const std::string& name){
  auto it = mGetUniformLocations.find(name);ECLIPSE_CHECK_GL_ERROR;
  if(it == mGetUniformLocations.end()){
    mGetUniformLocations[name] = glGetUniformLocation(mProgramId,name.c_str());ECLIPSE_CHECK_GL_ERROR;
  }
  return mGetUniformLocations[name];
}


} // namespace eclipse::graphics
