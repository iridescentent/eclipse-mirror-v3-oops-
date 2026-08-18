#include "rendercommands.h"
#include <memory>
#include "mesh.h"
#include "shader.h"
#include <glad/glad.h>

namespace eclipse::graphics::rendercommands{
  void RenderMesh::Execute(){
    std::shared_ptr<mesh>mesh = mMesh.lock();
    std::shared_ptr<shader>shader = mShader.lock();

    if(mesh&&shader){
      mesh ->Bind();
      shader -> Bind();
      glDrawArrays(GL_TRIANGLE_STRIP,0,mesh ->GetVertexCount());
      mesh ->Unbind();
      shader ->Unbind();
    }

  }
}
