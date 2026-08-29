#pragma once

#include <SDL2/SDL.h>

namespace eclipse::core {
class imguiwindow {
 public:
  bool Initialize(SDL_Window* window, SDL_GLContext context);
  void Shutdown();
  void ProcessEvent(const SDL_Event* event);
  void NewFrame();
  void Render();
};
}  // namespace eclipse::core
