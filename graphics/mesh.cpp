#include "mesh.h"
#include "../src/log.h"
#include <cstdint>
#include <glad/glad.h>
#include "helpers.h"


namespace eclipse::graphics{
  mesh::mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions):mVertexCount(vertexCount){
    glGenVertexArrays(1,&mVao); ECLIPSE_CHECK_GL_ERROR;
    glBindVertexArray(mVao); ECLIPSE_CHECK_GL_ERROR;
    glGenBuffers(1,&mPositionVbo); ECLIPSE_CHECK_GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo);ECLIPSE_CHECK_GL_ERROR;
    glBufferData(GL_ARRAY_BUFFER,vertexCount * sizeof(float) * dimensions, vertexArray, GL_STATIC_DRAW );ECLIPSE_CHECK_GL_ERROR;

    glEnableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;
    glVertexAttribPointer(0,dimensions,GL_FLOAT,GL_FALSE,0,0);ECLIPSE_CHECK_GL_ERROR;
    glDisableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;

    glBindVertexArray(0);ECLIPSE_CHECK_GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER,0);ECLIPSE_CHECK_GL_ERROR;
  }

void mesh::Bind(){
  glBindVertexArray(mVao);ECLIPSE_CHECK_GL_ERROR;
  glEnableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;
}

void mesh::Unbind(){
  glDisableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;
  glBindVertexArray(0);ECLIPSE_CHECK_GL_ERROR;
}



  mesh::~mesh(){
    glDeleteBuffers(1,&mPositionVbo);ECLIPSE_CHECK_GL_ERROR;
    glDeleteVertexArrays(1,&mVao);ECLIPSE_CHECK_GL_ERROR;
  }  
}
