#include <SDL2/SDL.h>
#include "window.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_video.h"
#include "../src/log.h"
#include "../src/engine.h"
#include <glad/glad.h>

namespace eclipse::core{
  window::window():mWindow(nullptr){
    
  }

  window::~window(){
    if(mWindow){
      Shutdown();
    }
  }

  bool window::Create(){
    mWindow = SDL_CreateWindow("eclipse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(!mWindow){
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
if(!mWindow){
  ECLIPSE_ERROR("Error Creating GL Context {}",SDL_GetError());
}

gladLoadGLLoader(SDL_GL_GetProcAddress);

// glEnable(GL_DEPTH_TEST);
// glDepthFunc(GL_LEQUAL);
// glEnable(GL_BLEND);
// glBlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);
// glClearColor(0,0,255,255);

    return true;
}

void window::BeginRender(){
  engine::Instance().GetRenderManager().Clear();
}

void window::EndRender(){
  SDL_GL_SwapWindow(mWindow);
}

  void window::Shutdown(){
    SDL_DestroyWindow(mWindow);    
    mWindow = nullptr;
  }

  void window::PollEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      switch(event.type){
        case SDL_QUIT:
          engine::Instance().Quit();
        default:
          break;
      }
    }
  }
}
