#include "window.hpp"

/*
void Window::onEvent(SDL_Event const &event) {
  // Keyboard events
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_SPACE)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Fire));
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Up));
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Down));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Right));
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_SPACE)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Fire));
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Up));
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Down));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Right));
  }

  // Mouse events
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Fire));
    if (event.button.button == SDL_BUTTON_RIGHT)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Up));
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_LEFT)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Fire));
    if (event.button.button == SDL_BUTTON_RIGHT)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Up));
  }
  if (event.type == SDL_MOUSEMOTION) {
    glm::ivec2 mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    glm::vec2 direction{mousePosition.x - m_viewportSize.x / 2,
                        -(mousePosition.y - m_viewportSize.y / 2)};

    m_ship.m_rotation = std::atan2(direction.y, direction.x) - M_PI_2;
  }
}
*/

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  // Load a new font
  auto const filename{assetsPath + "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 60.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError("Cannot load font file");
  }

  // Create program to render the other objects
  m_objectsProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "effects.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "effects.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);

#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
#endif

  // Start pseudo-random number generator
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  restart();
}

void Window::restart() {
  m_state = State::Idle;

  m_slash.create(m_objectsProgram);
}

void Window::onUpdate() {
  /*
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  // Wait 5 seconds before restarting
  if (m_gameData.m_state != State::Playing &&
      m_restartWaitTimer.elapsed() > 5) {
    restart();
    return;
  }
  */
  // m_ship.update(m_gameData, deltaTime);
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
  if (m_state == State::AttackAnimation) {
    m_slash.paint();
  }
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();
  {
    /*
    auto const size{ImVec2(300, 85)};
    auto const position{ImVec2((m_viewportSize.x - size.x) / 2.0f,
                               (m_viewportSize.y - size.y) / 2.0f)};
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags const flags{ImGuiWindowFlags_NoBackground |
                                 ImGuiWindowFlags_NoTitleBar |
                                 ImGuiWindowFlags_NoInputs};
    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);

    if (m_state == State::GameOver) {
      ImGui::Text("Game Over!");
    } else if (m_state == State::Win) {
      ImGui::Text("*You Win!*");
    }
    ImGui::PopFont();
    ImGui::End();
    */

    abcg::OpenGLWindow::onPaintUI();
    {
      ImGui::SetNextWindowPos({0, m_viewportSize.y - 100.0f});
      ImGui::SetNextWindowSize({m_viewportSize.x - 0.0f, 200});
      ImGuiWindowFlags const flags{ImGuiWindowFlags_NoBackground};

      ImGui::Begin(" ", nullptr, flags);

      static float crit{5};

      static int atk{1};

      static int dmg{};
      static float critchance{};

      if (m_state == State::Idle) {
        bool nh{}, sa{}, im{};

        if (ImGui::Button("Normal Hit")) {
          nh = true;
          atk = 1;
        }
        ImGui::SameLine();
        if (ImGui::Button("Slash Attack")) {
          sa = true;
          atk = 2;
        }
        ImGui::SameLine();
        if (ImGui::Button("Ice Magic")) {
          im = true;
          atk = 3;
        }
        ImGui::SliderFloat("Crit Chance", &crit, 5.0f, 100.0f);

        if (nh || sa || im) {
          m_state = State::AttackAnimation;
        }

        nh = false;
        sa = false;
        im = false;

        std::uniform_int_distribution rdmg(1, 30);
        std::uniform_real_distribution rcrit(0.0f, 100.0f);

        dmg = rdmg(m_randomEngine);
        critchance = rcrit(m_randomEngine);

      } else if (m_state == State::AttackAnimation) {
        // std::uniform_int_distribution rdmg(1, 30);
        // int dmg{rdmg(m_randomEngine)};

        // std::uniform_real_distribution rcrit(0.0f, 100.0f);
        // float critchance = rcrit(m_randomEngine);

        switch (atk) {
        case 1:
          ImGui::Text("You used [Normal Hit]");
          break;
        case 2:

          ImGui::Text("You used [Slash Attack]");
          m_slash.paint();
          break;
        case 3:

          ImGui::Text("You used [Ice Magic]");
          break;
        }

        atk = 0;

        if (critchance > crit) {
          ImGui::Text("It caused %d of damage", dmg);
        } else {
          ImGui::Text("It caused %d of damage", dmg * 2);
        }

        if (ImGui::Button("Teste")) {
          m_state = State::Idle;
        }
      }
    }
  }
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_objectsProgram);

  m_slash.destroy();
}