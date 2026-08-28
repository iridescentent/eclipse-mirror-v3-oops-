#pragma once
#include <SDL2/SDL.h>
#include <SDL_video.h>

struct SDL_Window;
using SDL_GLContext = void*;

namespace eclipse::core{
  class window{
    public:
      window();
      ~window();
      bool Create();
      void Shutdown();
      void PollEvents();
      void BeginRender();
      void EndRender();
      
    private:
      SDL_Window* mWindow;
      SDL_GLContext mGLContext;      
  };
}
