#include "window.hpp"

int main(int argc, char **argv) {
  try {
    abcg::Application app(argc, argv);

    Window window;
    window.setOpenGLSettings({.samples = 10});
    window.setWindowSettings({//.width,
                              //.height,
                              .showFPS = false,
                              .showFullscreenButton = false,
                              .title = "Atividade 2"});

    app.run(window);
  } catch (std::exception const &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}