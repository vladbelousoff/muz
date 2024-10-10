#include <muz/scope_exit.h>
#include <muz/string.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

void
show_dock_space()
{
   constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                                             ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration;

   ImGuiViewport* viewport = ImGui::GetMainViewport();
   ImGui::SetNextWindowPos(viewport->Pos);
   ImGui::SetNextWindowSize(viewport->Size);
   ImGui::SetNextWindowViewport(viewport->ID);

   ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

   ImGui::Begin("Muz DockSpace Window", nullptr, window_flags);

   ImGui::PopStyleVar();

   if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
         if (ImGui::MenuItem("New")) {
         }
         if (ImGui::MenuItem("Open", "Ctrl+O")) {
         }
         if (ImGui::MenuItem("Save", "Ctrl+S")) {
         }
         ImGui::Separator();
         if (ImGui::MenuItem("Exit", "Alt+F4")) {
         }
         ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Edit")) {
         if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
         }
         if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
         }
         ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
   }

   ImGui::DockSpace(ImGui::GetID("Default DockSpace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

   ImGui::Begin("Outliner");
   ImGui::Text("This is the Outliner window");
   ImGui::End();

   ImGui::Begin("Viewport");
   ImGui::Text("This is the Viewport window");
   ImGui::End();

   ImGui::Begin("World");
   ImGui::Text("This is the World window");
   ImGui::End();

   ImGui::End();
}

int
main(int, char**)
{
   if (!glfwInit()) {
      spdlog::error("Failed to initialize glfw!");
      return -1;
   }

   muzScopeExit terminate_glfw([]() {
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

   static muzStringView title = "Muz";
   GLFWwindow* window = glfwCreateWindow(1920, 1080, title.data(), nullptr, nullptr);
   if (!window) {
      spdlog::error("Failed to create a glfw window!");
      return -1;
   }

   muzScopeExit terminate_window([window]() {
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
   io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

   // Setup Dear ImGui style
   ImGui::StyleColorsLight();

   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 330");

   muzScopeExit terminate_imgui([]() {
      // Some ImGui cleanups here
      spdlog::info("Terminating ImGui...");
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
   });

   // Main loop
   while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      int display_w;
      int display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);

      // Basic render
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // Show DockSpace
      show_dock_space();

      // Rendering
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
   }
}
