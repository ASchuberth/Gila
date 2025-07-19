#include "pch.hpp"
#include "render.hpp"
#include "event.hpp"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

void run(CADERA_APP_NAMESPACE::CADRender &render) {

  render.setBGColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
  render.setup();
  render.initImgui();

}

void runImgui(Model* model) {

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Start Screen");

  static int modelTypeInt;
  ImGui::RadioButton("Sketch", &modelTypeInt, 0);
  ImGui::SameLine();
  ImGui::RadioButton("Part", &modelTypeInt, 1);

  if (ImGui::Button("Add Points")) {

    model->clearRender();
    model->addPoint(glm::vec3{1.0f,0.0f,1.0f});
    model->addPoint(glm::vec3{4.0f,0.0f,2.0f});
    model->addPoint(glm::vec3{2.0f,0.0f,2.0f});
    model->addPoint(glm::vec3{7.0f,0.0f,-4.0f});
    model->notify();
    

  }

  if (ImGui::Button("Delete Model")) {

    model->clearRender();
    model->notify();

  }

  ImGui::End();

  ImGui::Render();
}

int main() {

  CADERA_APP_NAMESPACE::CADRender render;

  try {
    run(render);
  }
  catch ( vk::SystemError & err )
  {
    std::cout << "vk::SystemError: " << err.what() << std::endl;
    exit( -1 );
  }
  catch ( std::exception & err )
  {
    std::cout << "std::exception: " << err.what() << std::endl;
    exit( -1 );
  }
  catch ( ... )
  {
    std::cout << "unknown error\n";
    exit( -1 );
  }

  Sketch S;
  Model M;

  S.addRender(&render);
  M.addRender(&render);

  S.addPoint(glm::vec3{0.0f,1.0f,2.0f});


  while (!glfwWindowShouldClose(render.mMainWindow)) {

    glfwPollEvents();

    runImgui(&M);

    render.createCommandBuffers();
    render.drawFrame();

    glfwWaitEvents();
  }

  render.destroy();

  glfwTerminate();

  return 0;
}