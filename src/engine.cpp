#include "engine.h"
#include "SDL2/SDL_error.h"
#include "log.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cstdint>
#include <memory>
#include "../graphics/mesh.h"
#include "../graphics/shader.h"


namespace eclipse{

engine::engine():mIsInitialized(false),mIsRunning(false){
  
}

engine::~engine(){
  
}

engine* engine::mInstance = nullptr;

engine& engine::Instance(){
  if(!mInstance){
    mInstance = new engine;
  }
  return *mInstance;
}

void engine::Run(){
  if(Initialize()){
    while(mIsRunning){
    
      // test mesh

      float vertices[]{
        -0.5f   ,-0.5f    ,0.f,
        0.f     ,0.5f     ,0.f,
        0.5f    ,-0.5f    ,0.f
      };

    // std::shared_ptr<graphics::mesh>mesh = std::make_shared<graphics::mesh>(&vertices[0],3,3);

      mWindow.PollEvents();
      mWindow.BeginRender();

    //   const char* vertexShader = R"(
    //       #version 410 core
    //       layout(location = 0) in vec3 position;
    //        int main(){
    //          gl_Position = vec4(position,1.0);
    //        }
    //     )";

        
    //   const char* fragmentShader = R"(
    //       #version 410 core
    //       out vec4 outColor;
    //        int main(){
    //          outColor = vec4(1.0);
    //        }
    //     )";

    // std::shared_ptr<graphics::shader>shader = std::make_shared<graphics::shader>(vertexShader,fragmentShader);



      std::shared_ptr<graphics::mesh> mesh = std::make_shared<graphics::mesh>(&vertices[0],3,3);

      const char* vertexShader = R"(
          #version 410 core
          layout (location = 0) in vec3;
          void main(){
            gl_Position = vec4(position,1.0);
          }
        )";

      const char* fragmentShader = R"(
          #version 410 core
          out vec4 outColor;
          void main(){
            outColor = vec4(1.0);
          }
        )";


        std::shared_ptr<graphics::shader>shader = std::make_shared<graphics::shader>(vertexShader,fragmentShader);


      auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh,shader);
      mRenderManager.Submit(std::move(rc));
      mRenderManager.Flush();
    
  
    

      mWindow.EndRender();
    }
    Shutdown();
  }
}

void engine::Quit(){
  mIsRunning = false;
}


bool engine::Initialize(){
  mLogManager.Initialize();
  ECLIPSE_ASSERT(!mIsInitialized, "Attempting to call engine more than once");
  GetInfo();
  bool ret = false;
  

  if(SDL_Init(SDL_INIT_EVERYTHING)<0){
    ECLIPSE_ERROR(" Error Initializing SDL {}",SDL_GetError());
    ret = false;
  }
  else{
    SDL_version version;
    SDL_VERSION(&version);
    ECLIPSE_INFO("SDL {}.{}.{}",(int)version.major,(int)version.minor,(int)version.patch);

    if(mWindow.Create()){

      mRenderManager.Initialize();

      ret = true;
      mIsInitialized = true;
      mIsRunning = true;  
    }
  }if(!ret){
    Shutdown();
  }
  return ret;
}

void engine::Shutdown(){
  mLogManager.Shutdown();
  mRenderManager.Shutdown();
  mIsRunning = false;
  mIsInitialized = false;
  mWindow.Shutdown();
  SDL_Quit();

}


void engine::GetInfo(){
#ifdef ECLIPSE_CONFIG_DEBUG
ECLIPSE_DEBUG("Configuration: DEBUG");
#endif
#ifdef ECLIPSE_CONFIG_RELEASE
ECLIPSE_DEBUG("Configuration: RELEASE");
#endif
#ifdef ECLIPSE_PLATFORM_MAC
ECLIPSE_WARN("Platform: MAC");
#endif
#ifdef ECLIPSE_PLATFORM_WINDOWS
ECLIPSE_WARN("Platform: WINDOWS");
#endif
#ifdef ECLIPSE_PLATFORM_LINUX
ECLIPSE_WARN("Platform: LINUX");
#endif
}

  
}
