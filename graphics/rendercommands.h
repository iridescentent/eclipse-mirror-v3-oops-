#pragma once

#include <memory>
namespace eclipse::graphics{
  class mesh;
  class shader;


namespace rendercommands{
  class RenderCommands{
    public:
      virtual void Execute() = 0;
      virtual ~RenderCommands(){}
  };
  class RenderMesh: public RenderCommands{
    public:
      virtual void Execute();
      RenderMesh(std::weak_ptr<mesh>mesh,std::weak_ptr<shader>shader):mMesh(mesh),mShader(shader){
        
      }
    private:
      std::weak_ptr<mesh>mMesh;
      std::weak_ptr<shader>mShader;
  };
}










}
