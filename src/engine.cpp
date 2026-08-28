#include "engine.h"
#include <SDL2/SDL.h>
#include "../graphics/mesh.h"
#include "../graphics/shader.h"
#include <SDL_error.h>
#include <SDL_version.h>
#include <cstdint>
#include <memory>
#include "log.h"
namespace eclipse{
  engine::engine():mIsInitialized(false),mIsRuning(false){
    
  };
  engine::~engine(){
    
  }

  engine* engine::mInstance = nullptr;
  engine& engine::Instance(){
    if(!mInstance){
      mInstance = new engine;
    }
    return *mInstance;
  }

  void engine::Run(App* app){
    if(Initialize()){
      while(mIsRuning){

      float vertices[]{
        0.5f,0.5f,0.f,
        0.5f,-0.5f,0.f,
        -0.5f,-0.5f,0.f,
        -0.5f,0.5f,0.f
      };

      uint32_t elements[]{
        0,3,1,
        1,3,2
      };

      std::shared_ptr<graphics::mesh>mesh = std::make_shared<graphics::mesh>(&vertices[0],4,3,&elements[0],6);

    const char *vertexShader = R"(
            #version 410 core
            layout(location = 0) in vec3 position;
            out vec3 vertexpos;
            void main(){
              vertexpos = position;
              gl_Position = vec4(position,1.0); 
            }
         )";

    const char *fragmentShader = R"(
            #version 410 core
            out vec4 outColor;
            in vec3 vertexpos;
            uniform vec3 color = vec3(0.0);
            void main(){
              outColor = vec4(vertexpos,1.0);
            }
         )";

         std::shared_ptr<graphics::shader>shader = std::make_shared<graphics::shader>(vertexShader,fragmentShader);

         shader -> SetUniformFloat3("color", 1, 0, 0);

        mWindow.PollEvents();

        mWindow.BeginRender();

        auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh,shader);
        mRenderManager.Submit(std::move(rc));
        mRenderManager.Flush();

        mWindow.EndRender();
        }
        Shutdown();
    }
  }
  void engine::Quit(){
    mIsRuning = false;
  }
  bool engine::Initialize(){
    bool ret = false;
    mLogManager.Initialize();
    ECLIPSE_ASSERT(!mIsInitialized, "Tryint to reinitialize engine");
    GetInfo();
    if(SDL_Init(SDL_INIT_EVERYTHING)>0){
      ECLIPSE_ERROR("Error initializing SDL {}",SDL_GetError());
      ret = false;
    }else{
      SDL_version version;
      SDL_VERSION(&version);
      ECLIPSE_INFO("SDL {}.{}.{}",(int)version.major ,(int)version.minor,(int)version.patch);
      if(mWindow.Create()){
        mRenderManager.Initialize();
        ret = true;
        mIsInitialized = true;
        mIsRuning = true;
      }
    }
    return ret;
  };
  void engine::Shutdown(){
    mLogManager.Shutdown();
    mRenderManager.Shutdown();
    mWindow.Shutdown();
    mIsInitialized = false;
    mIsRuning = false;
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
    #ifdef ECLIPSE_PLATFORM_LINUX
    ECLIPSE_WARN("Platform: LINUX");
    #endif
    #ifdef ECLIPSE_PLATFORM_WINDOWS
    ECLIPSE_WARN("Platform: WINDOWS");
    #endif
  }
}
