#pragma once
#include "log.h"
#include "../core/window.h"
#include "app.h"
#include "../managers/rendermanager.h"
namespace eclipse{
  class engine{
    public:
      static engine& Instance();
      void Quit();
      void Run(App* app);
      inline App& GetApp(){return* mApp;}
      inline managers::RenderManager& GetRenderManager(){return mRenderManager;}
      inline core::window& GetWindow(){return mWindow;}
    private:
      static engine* mInstance;
      core::window mWindow;
      App* mApp;
      managers::LogManager mLogManager;
      managers::RenderManager mRenderManager;
      bool mIsInitialized;
      bool mIsRuning;
      engine();
      ~engine();
      bool Initialize();
      void Shutdown();
      void GetInfo();
  };
}
