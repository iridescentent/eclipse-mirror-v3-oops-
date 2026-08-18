#pragma once

#include <cstdint>
namespace eclipse::graphics{
  class mesh{
    public:
      mesh(float* vertexArray, uint32_t vertexCount , uint32_t dimensions);
      ~mesh();
      void Bind();
      void Unbind();
      inline uint32_t GetVertexCount(){return mVertexCount;}
    private:
      uint32_t mVertexCount;
      uint32_t mVao;
      uint32_t mPositionVbo;
    
  };
}
