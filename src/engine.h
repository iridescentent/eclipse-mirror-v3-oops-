#pragma once
#include "log.h"
#include "../core/window.h"
#include "../managers/rendermanager.h"
namespace eclipse{
  class engine{

    public:
      static engine& Instance();      
      void Run();
      void Quit();
      inline managers::RenderManager& GetRenderManager(){return mRenderManager;}


    private:
      engine();
      ~engine();

      static engine* mInstance;

      core::window mWindow;
      managers::LogManager mLogManager;
      managers::RenderManager mRenderManager;



      bool mIsInitialized;
      bool mIsRunning;

      
      [[nodiscard]]bool Initialize();
      void Shutdown();
      void GetInfo();



  };
}
