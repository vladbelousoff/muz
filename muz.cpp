#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <muz/scope_exit.h>
#include <muz/string.h>

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
   }

   muz::ScopeExit terminate_window([window]() {
      spdlog::info("Terminating window...");
      glfwDestroyWindow(window);
   });

   // Make the window's context current
   glfwMakeContextCurrent(window);

   // VSYNC
   glfwSwapInterval(1);

   if (gl3wInit()) {
      spdlog::error("Failed to initialize gl3w!");
      return -1;
   }

   // Main loop
   while (!glfwWindowShouldClose(window)) {
      glfwSwapBuffers(window);
      glfwPollEvents();
   }
}
