#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

int
main(int argc, char** argv)
{
   int xpos, ypos, height;
   const char* description;
   GLFWwindow* windows[4];

   if (!glfwInit()) {
      glfwGetError(&description);
      printf("Error: %s\n", description);
      exit(EXIT_FAILURE);
   }

   glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

   glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xpos, &ypos, nullptr, &height);

   for (int i = 0; i < 4; i++) {
      const int size = height / 5;

      const struct
      {
         float r, g, b;
      } colors[] = { { 0.95f, 0.32f, 0.11f }, { 0.50f, 0.80f, 0.16f }, { 0.f, 0.68f, 0.94f }, { 0.98f, 0.74f, 0.04f } };

      if (i > 0) {
         glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
      }

      glfwWindowHint(GLFW_POSITION_X, xpos + size * (1 + (i & 1)));
      glfwWindowHint(GLFW_POSITION_Y, ypos + size * (1 + (i >> 1)));

      windows[i] = glfwCreateWindow(size, size, "Multi-Window Example", NULL, NULL);
      if (!windows[i]) {
         glfwGetError(&description);
         printf("Error: %s\n", description);
         glfwTerminate();
         exit(EXIT_FAILURE);
      }

      glfwSetInputMode(windows[i], GLFW_STICKY_KEYS, GLFW_TRUE);

      glfwMakeContextCurrent(windows[i]);

      if (gl3wInit()) {
         fprintf(stderr, "failed to initialize OpenGL\n");
         return -1;
      }
      if (!gl3wIsSupported(3, 2)) {
         fprintf(stderr, "OpenGL 3.2 not supported\n");
         return -1;
      }

      printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

      glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);
   }

   for (;;) {
      for (int i = 0; i < 4; i++) {
         glfwMakeContextCurrent(windows[i]);
         glClear(GL_COLOR_BUFFER_BIT);
         glfwSwapBuffers(windows[i]);

         if (glfwWindowShouldClose(windows[i]) || glfwGetKey(windows[i], GLFW_KEY_ESCAPE)) {
            glfwTerminate();
            exit(EXIT_SUCCESS);
         }
      }

      glfwWaitEvents();
   }
}
