#include "imguiwindow.h"

#include "../eclipse/include/external/imgui/imgui.h"
#include "../eclipse/include/external/imgui/imgui_impl_opengl3.h"
#include "../eclipse/include/external/imgui/imgui_impl_sdl2.h"
#include <glad/glad.h>

namespace eclipse::core {
bool imguiwindow::Initialize(SDL_Window* window, SDL_GLContext context) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImGui::StyleColorsDark();

  if (!ImGui_ImplSDL2_InitForOpenGL(window, context) ||
      !ImGui_ImplOpenGL3_Init("#version 410 core")) {
    Shutdown();
    return false;
  }
  return true;
}

void imguiwindow::Shutdown() {
  if (ImGui::GetCurrentContext() == nullptr) {
    return;
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void imguiwindow::ProcessEvent(const SDL_Event* event) {
  if (ImGui::GetCurrentContext() != nullptr) {
    ImGui_ImplSDL2_ProcessEvent(event);
  }
}

void imguiwindow::NewFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
}

void imguiwindow::Render() {
  ImGui::Render();
  int width = 0;
  int height = 0;
  SDL_GL_GetDrawableSize(SDL_GL_GetCurrentWindow(), &width, &height);
  glViewport(0, 0, width, height);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
}  // namespace eclipse::core
