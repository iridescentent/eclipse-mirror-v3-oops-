#pragma once
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>

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
