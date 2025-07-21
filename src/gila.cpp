#include "gila.hpp"
#include "pch.hpp"

namespace GILA_APP_NAMESPACE {

void Gila::mainLoop() {

  while (!glfwWindowShouldClose(mRender.mMainWindow)) {

    glfwPollEvents();

    runImgui();

    mRender.createCommandBuffers();
    mRender.drawFrame();

    glfwWaitEvents();
  }

  mRender.destroy();

  glfwTerminate();
}

void Gila::runImgui() {
  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Start Screen");

  static int modelTypeInt;
  ImGui::RadioButton("Sketch", &modelTypeInt, 0);
  ImGui::SameLine();
  ImGui::RadioButton("Part", &modelTypeInt, 1);

  if (ImGui::Button("Add Points")) {
  }

  if (ImGui::Button("Delete Model")) {
  }

  ImGui::End();

  ImGui::Render();
}

void Gila::run() {
  mRender.setBGColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
  mRender.setup();
  mRender.initImgui();

  mainLoop();
}

} // namespace GILA_APP_NAMESPACE
