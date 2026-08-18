#pragma once
#include "../graphics/rendercommands.h"
#include <memory>
#include <queue>
namespace eclipse::managers{
  class RenderManager{
   public:
    void Initialize();
    void Shutdown();
    RenderManager();
    ~RenderManager();
    void Submit(std::unique_ptr<graphics::rendercommands::RenderCommands>rc);
    void Flush();
    void Clear();
    void SetClearColor(float r , float g , float b , float a );
    private:
      std::queue<std::unique_ptr<graphics::rendercommands::RenderCommands>>mRenderCommands;
  };
}
