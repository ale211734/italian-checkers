# Dipendenze installate da vcpkg.json (manifest mode, vedi CMakePresets.json).
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(dama_gui
  main.cpp
  app.cpp
  app.h
  platform/window.cpp
  platform/window.h
  platform/glfw_context.h
  input/keyboard.cpp
  input/keyboard.h
  renderer/board_renderer.cpp
  renderer/board_renderer.h
  renderer/camera.h
  renderer/piece_renderer.cpp
  renderer/piece_renderer.h
  renderer/shader.cpp
  renderer/shader.h
  ui/ui.cpp
  ui/ui.h
)

target_include_directories(dama_gui PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
# glad.h fornisce le dichiarazioni OpenGL: impedisce a GLFW e ImGui di includere <GL/gl.h>.
target_compile_definitions(dama_gui PRIVATE GLFW_INCLUDE_NONE IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(dama_gui PRIVATE
  dama_engine glfw glad::glad imgui::imgui glm::glm OpenGL::GL
)
