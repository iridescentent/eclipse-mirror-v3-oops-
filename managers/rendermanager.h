#pragma once
#include "../graphics/rendercommands.h"
#include <memory>
#include <queue>

namespace eclipse::managers{
  class RenderManager{
    public:
      RenderManager();
      ~RenderManager();
      void Initialize();
      void Shutdown();
      void Clear();
      void SetClearColor(float r , float g , float b , float a );
      void Submit(std::unique_ptr<graphics::rendercommands::RenderCommands>rc);
      void Flush();
      void SetWireFrameMode(bool enabled);
    private:
      std::queue<std::unique_ptr<graphics::rendercommands::RenderCommands>>mRenderCommands;
  };
}
