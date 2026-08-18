#include "rendermanager.h"
#include "../src/log.h"
#include <algorithm>
#include <glad/glad.h>
#include <utility>

namespace eclipse::managers{

    RenderManager::RenderManager(){
          
    }

    RenderManager::~RenderManager(){
      
    }


    void RenderManager::Initialize(){
      ECLIPSE_INFO("Opengl info: \t Renderer: \t{}\n Vendor: \t{}\n Version: \t{}",
                   (const char*)glGetString(GL_RENDERER),
                   (const char*)glGetString(GL_VENDOR),
                   (const char*)glGetString(GL_VERSION))

      
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);
      glClearColor(0,0,255,255);

    }
    void RenderManager::Shutdown(){
      if(mRenderCommands.size()>0){
        mRenderCommands.pop();
      }
    }
       
    void RenderManager::Submit(std::unique_ptr<graphics::rendercommands::RenderCommands>rc){
      mRenderCommands.push(std::move(rc));
    }
    void RenderManager::Flush(){
      while(mRenderCommands.size()>0){
        auto rc = std::move(mRenderCommands.front());
        mRenderCommands.pop();
        rc ->Execute();
      }
    }
    void RenderManager::Clear(){

ECLIPSE_ASSERT(mRenderCommands.size() == 0, "unflushed render commands in queue")
      
      while(mRenderCommands.size()>0){
        mRenderCommands.pop();
      }

      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    void RenderManager::SetClearColor(float r , float g , float b , float a ){
      glClearColor(r,g,b,a);
    }
}
