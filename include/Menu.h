#include <../thirdparty/imgui-docking/imgui/backends/imgui_impl_glfw.h>
#include <../thirdparty/imgui-docking/imgui/backends/imgui_impl_opengl3.h>
#include <imgui.h>
float BG_RED = 0.0f;
float BG_GREEN = 0.0f;
float BG_BLUE = 0.0f;
float BG_ALPHA = 1.0f;

float SC_RED = 1.0f;
float SC_GREEN = 1.0f;
float SC_BLUE = 1.0f;
float SC_ALPHA = 1.0f;

float ambientLight = 1.0f;
float specularLight = 0.2f;
float diffuseLight = 0.2f;

bool wireframe = false;
bool vsync = true;
bool depthtest = true;

float lightpos1 = 0.2f;
float lightpos2 = 0.5f;
float lightpos3 = 0.2f;
float lightscale = 2.0f;
float lightrotation = 0.0f;

float Camerasensitivity = 100.0f;
float Cameraspeed = 0.01f;
float Camerafov = 45.0f;
float Cameranearplane = 0.1f;
float Camerafarplane = 100.0f;

bool show_light_window;
bool show_light_colour_window;
bool show_lighting_window;
bool show_lightpyramid_window;
bool show_background_colour_window;
bool show_controls_window;
bool show_options_window;
bool show_pyramid_window;

int ambientLighting;
int specularLighting;
int diffuseLighting;

void MenuIMGUI(void) {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;              // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport /
                                                      // Platform Windows
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::SetWindowPos(
      ImVec2(io.DisplaySize.x / 2 - ImGui::GetWindowWidth() / 2, 0));
  if (ImGui::Begin("Menu")) {
    ImGui::SetWindowSize(ImVec2(250, 200));

    ImGui::Checkbox("show_controls_window", &show_controls_window);
    ImGui::Checkbox("show_background_colour_window",
                    &show_background_colour_window);
    ImGui::Checkbox("show_light_colour_window", &show_light_colour_window);
    ImGui::Checkbox("show_options_window", &show_options_window);
    ImGui::Checkbox("show_lighting_window", &show_lighting_window);
    ImGui::Checkbox("show_pyramid_window", &show_pyramid_window);
    ImGui::Checkbox("show_light_window", &show_light_window);

    if (show_controls_window == true) {
      ImGui::SetWindowSize(ImVec2(250, 200));
      ImGui::Begin("show_controls_window");
      ImGui::Checkbox("show_controls_window", &show_controls_window);
      ImGui::Text("The controls are WASD to move around , Space/Ctrl to go up");
      ImGui::Text("and down and hold right click to look around");
      ImGui::SliderFloat("Camera-Speed", &Cameraspeed, 0.0f, 1.0f);
      ImGui::SliderFloat("Camera-Sensitivity", &Camerasensitivity, 0.0f,
                         1000.0f);
      ImGui::SliderFloat("Camera-FOV", &Camerafov, -360.f, 360.f);
      ImGui::SliderFloat("Camera-nearplane", &Cameranearplane, 0.f, 10.f);
      ImGui::SliderFloat("Camera-farplane", &Camerafarplane, 0.f, 1000.f);
      ImGui::End();
    }
    if (show_background_colour_window == true) {
      ImGui::SetWindowSize(ImVec2(250, 200));
      ImGui::Begin("show_background_colour_window");
      ImGui::Checkbox("show_background_colour_window",
                      &show_background_colour_window);
      ImGui::SliderFloat("BG_Red", &BG_RED, 0.0f, 1.0f);
      ImGui::SliderFloat("BG_Green", &BG_GREEN, 0.0f, 1.0f);
      ImGui::SliderFloat("BG_Blue", &BG_BLUE, 0.0f, 1.0f);
      ImGui::SliderFloat("BG_Alpha", &BG_ALPHA, 0.0f, 1.0f);
      ImGui::End();
    }
    if (show_light_colour_window == true) {
      ImGui::Begin("show_light_colour_window");
      ImGui::Checkbox("show_light_colour_window", &show_light_colour_window);
      ImGui::SliderFloat("SC_Red", &SC_RED, 0.0f, 1.0f);
      ImGui::SliderFloat("SC_Green", &SC_GREEN, 0.0f, 1.0f);
      ImGui::SliderFloat("SC_Blue", &SC_BLUE, 0.0f, 1.0f);
      ImGui::SliderFloat("SC_Alpha", &SC_ALPHA, 0.0f, 1.0f);
      ImGui::End();
    }
    if (show_options_window == true) {
      ImGui::Begin("show_options_window");
      ImGui::Checkbox("show_options_window", &show_options_window);
      ImGui::Checkbox("wireframe", &wireframe);
      ImGui::Checkbox("vsync", &vsync);
      ImGui::Checkbox("depth_test", &depthtest);
      ImGui::End();
    }
    if (show_lighting_window == true) {
      ImGui::SetNextWindowSize(ImVec2(350, 125));
      ImGui::Begin("show_lighting_window");
      ImGui::Checkbox("show_lighting_window", &show_lighting_window);
      if (ImGui::SliderFloat("Ambient_Light", &ambientLight, 0.0f, 1.0f)) {

        glUniform1f(ambientLighting, ambientLight);
      }
      if (ImGui::SliderFloat("Diffuse_Light", &diffuseLight, 0.0f, 1.0f)) {

        glUniform1f(diffuseLighting, diffuseLight);
      }
      if (ImGui::SliderFloat("Specular_Light", &specularLight, 0.0f, 1.0f)) {

        glUniform1f(specularLighting, specularLight);
      }
      ImGui::End();
    }

    if (show_light_window == true) {
      ImGui::SetNextWindowSize(ImVec2(525, 175));
      ImGui::Begin("show_light_window");
      ImGui::Checkbox("show_light_window", &show_light_window);
      ImGui::SliderFloat("Light-position X axis", &lightpos1, -10.0f, 10.0f);
      ImGui::SliderFloat("Light-position Y axis", &lightpos2, -10.0f, 10.0f);
      ImGui::SliderFloat("Light-position Z axis", &lightpos3, -10.0f, 10.0f);
      ImGui::SliderFloat("Light-Scale", &lightscale, -10.0f, 10.0f);
      ImGui::SliderFloat("Light-Rotation", &lightrotation, -360.0f, 360.0f);
      ImGui::End();
    }
    ImGui::End();
  }
  if (wireframe == true) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (wireframe == false) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  if (depthtest == true) {
    glEnable(GL_DEPTH_TEST);
  }
  if (depthtest == false) {
    glDisable(GL_DEPTH_TEST);
  }
}
