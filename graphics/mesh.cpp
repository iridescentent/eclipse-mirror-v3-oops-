#include "mesh.h"
#include <algorithm>
#include <glad/glad.h>
#include "../src/log.h"
#include "helpers.h"

namespace eclipse::graphics{

mesh::mesh(float *vertexArray, uint32_t vertexCount, uint32_t dimensions)
:mVertexCount(vertexCount),mVao(0),mEbo(0),mElementCount(0)
{
  
  
  glGenVertexArrays(1, &mVao);ECLIPSE_CHECK_GL_ERROR;
  glBindVertexArray(mVao);ECLIPSE_CHECK_GL_ERROR;
  glGenBuffers(1, &mPositionVbo);ECLIPSE_CHECK_GL_ERROR;
  glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo);ECLIPSE_CHECK_GL_ERROR;
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * dimensions,
               vertexArray, GL_STATIC_DRAW);ECLIPSE_CHECK_GL_ERROR;
  glEnableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;
  glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);ECLIPSE_CHECK_GL_ERROR;
  glDisableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;
  glBindVertexArray(0);ECLIPSE_CHECK_GL_ERROR;
  glBindBuffer(GL_ARRAY_BUFFER, 0);ECLIPSE_CHECK_GL_ERROR;
}
mesh::mesh(float *vertexArray, uint32_t vertexCount, uint32_t dimensions,uint32_t *elementArray, uint32_t elementCount)
:mesh(vertexArray,vertexCount,dimensions)

 {
   mElementCount = elementCount;
  // glGenVertexArrays(1, &mVao);ECLIPSE_CHECK_GL_ERROR;
  glBindVertexArray(mVao);ECLIPSE_CHECK_GL_ERROR;
  glGenBuffers(1, &mEbo);ECLIPSE_CHECK_GL_ERROR;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);ECLIPSE_CHECK_GL_ERROR;
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * elementCount ,
               elementArray, GL_STATIC_DRAW);ECLIPSE_CHECK_GL_ERROR;
  // glEnableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;
  // glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);ECLIPSE_CHECK_GL_ERROR;
  // glDisableVertexAttribArray(0);ECLIPSE_CHECK_GL_ERROR;
  glBindVertexArray(0);ECLIPSE_CHECK_GL_ERROR;
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);ECLIPSE_CHECK_GL_ERROR;
  
}
mesh::~mesh() {
  glDeleteVertexArrays(1,&mVao);
  if(mEbo != 0){
    glDeleteBuffers(1,&mEbo);
  }
  glDeleteBuffers(1,&mPositionVbo);
}
void mesh::Bind() {
  glBindVertexArray(mVao);
  glEnableVertexAttribArray(0);
}
void mesh::Unbind() {
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}
} // namespace eclipse::graphics
