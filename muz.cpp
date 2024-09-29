#include <muz/scope_exit.h>
#include <muz/string.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

int
main(int, char**)
{
   if (!glfwInit()) {
      spdlog::error("Failed to initialize glfw!");
      return -1;
   }

   muz::ScopeExit terminate_glfw([]() {
      spdlog::info("Terminating glfw...");
      glfwTerminate();
   });

   glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   glfwSetErrorCallback([](int error, const char* description) {
      spdlog::error("Error code: {}", error);
      spdlog::error("Error description: {}", description);
   });

   static muz::StringView title = "Muz";
   GLFWwindow* window = glfwCreateWindow(1920, 1080, title.data(), nullptr, nullptr);
   if (!window) {
      spdlog::error("Failed to create a glfw window!");
      return -1;
   }

   muz::ScopeExit terminate_window([window]() {
      spdlog::info("Terminating window...");
      glfwDestroyWindow(window);
   });

   // Make the window's context current
   glfwMakeContextCurrent(window);

   // VSYNC
   glfwSwapInterval(1);

   // gl3w
   if (gl3wInit()) {
      spdlog::error("Failed to initialize gl3w!");
      return -1;
   }

   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();

   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO();
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

   // Setup Dear ImGui style
   ImGui::StyleColorsLight();

   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 330");

   muz::ScopeExit terminate_imgui([]() {
      // Some ImGui cleanups here
      spdlog::info("Terminating ImGui...");
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
   });

   // Main loop
   while (!glfwWindowShouldClose(window)) {
      // Basic render

      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
      glfwPollEvents();
   }
}
