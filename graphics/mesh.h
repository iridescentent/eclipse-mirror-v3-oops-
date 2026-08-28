#pragma once

#include <cstdint>
namespace eclipse::graphics{
  class mesh{
    public:
      mesh(float* vertexArray, uint32_t vertexCount , uint32_t dimensions);
      mesh(float* vertexArray, uint32_t vertexCount , uint32_t dimensions,uint32_t* elementArray, uint32_t elementCount);
      ~mesh();
      void Bind();
      void Unbind();

      inline uint32_t GetVertexCount(){return mVertexCount;}
      inline uint32_t GetElementCount(){return mElementCount;}
    private:
      uint32_t mVertexCount , mElementCount;
      uint32_t mVao, mEbo;
      uint32_t mPositionVbo;
  };
}
