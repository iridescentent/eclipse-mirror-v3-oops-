#include "window.h"
#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_video.h>
#include "../src/log.h"
#include "../src/engine.h"
#include <glad/glad.h>
namespace eclipse::core{
  window::window():mWindow(nullptr),mGLContext(nullptr){
    
  };
  window::~window(){
    if(mWindow){
      Shutdown();
    }
  }
  bool window::Create(){
    mWindow = SDL_CreateWindow("eclipse", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!mWindow) {
      ECLIPSE_ERROR("Error Creating SDL Window {}",SDL_GetError());
      return false;
    }

#ifdef ECLIPSE_PLATFORM_MAC
SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif

SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_SetWindowMinimumSize(mWindow, 200, 200);

mGLContext = SDL_GL_CreateContext(mWindow);
if(!mGLContext){
  ECLIPSE_ERROR("Error creating SDL GL Context {}",SDL_GetError());
  SDL_DestroyWindow(mWindow);
  mWindow = nullptr;
  return false;
}

if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
  ECLIPSE_ERROR("Error loading OpenGL functions");
  Shutdown();
  return false;
}

if (!mImGui.Initialize(mWindow, mGLContext)) {
  ECLIPSE_ERROR("Error initializing ImGui");
  Shutdown();
  return false;
}

// glEnable(GL_DEPTH_TEST);
// glDepthFunc(GL_LEQUAL);
// glEnable(GL_BLEND);
// glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
// glClearColor(0,0,255,255);

    return true;
  }
  void window::BeginRender(){
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    engine::Instance().GetRenderManager().Clear();
    mImGui.NewFrame();
  }

  void window::EndRender(){
    mImGui.Render();
    SDL_GL_SwapWindow(mWindow);
  }

  
  void window::Shutdown(){
    mImGui.Shutdown();
    SDL_DestroyWindow(mWindow);
    SDL_GL_DeleteContext(mGLContext);
    mGLContext = nullptr;
    mWindow = nullptr;
  }
  void window::PollEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      mImGui.ProcessEvent(&event);
      switch(event.type){
        case SDL_QUIT:
          engine::Instance().Quit();
        default:
          break;
      }
    }
  }

  
}
