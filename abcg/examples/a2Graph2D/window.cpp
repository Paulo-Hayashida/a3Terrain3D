#include "window.hpp"

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  // Create program to render the objects
  m_effectsProgram =
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
  m_gameState = GameState::Idle;

  m_hit.create(m_effectsProgram);
  m_slash.create(m_effectsProgram);
  m_ice.create(m_effectsProgram);
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  // Wait 10 seconds before restarting
  if (m_gameState != GameState::Idle) {
    if (m_waitingTime.elapsed() > 10) {
      m_gameState = GameState::Idle;
      return;
    }
  } else {
    m_waitingTime.restart();
  }
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
  if (m_gameState != GameState::Idle) {
    switch (m_atktype) {
    case 1:
      m_hit.paint();
      break;
    case 2:
      m_slash.paint();
      break;
    case 3:
      m_ice.paint();
      break;
    }
  }
}

void Window::onPaintUI() {

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

    if (m_gameState == GameState::Idle) {
      bool nh{}, sa{}, im{};

      if (ImGui::Button("Normal Hit")) {
        nh = true;
        atk = 1;
        m_atktype = 1;
      }
      ImGui::SameLine();
      if (ImGui::Button("Slash Attack")) {
        sa = true;
        atk = 2;
        m_atktype = 2;
      }
      ImGui::SameLine();
      if (ImGui::Button("Ice Magic")) {
        im = true;
        atk = 3;
        m_atktype = 3;
      }
      ImGui::SliderFloat("Crit Chance", &crit, 5.0f, 100.0f);

      if (nh || sa || im) {
        m_gameState = GameState::AttackAnimation;
      }

      nh = false;
      sa = false;
      im = false;

      std::uniform_int_distribution rdmg(1, 30);
      std::uniform_real_distribution rcrit(0.0f, 100.0f);

      dmg = rdmg(m_randomEngine);
      critchance = rcrit(m_randomEngine);

    } else if (m_gameState == GameState::AttackAnimation) {
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

      if (ImGui::Button("Return")) {
        m_gameState = GameState::Idle;
      }
    }
  }
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_effectsProgram);

  m_hit.destroy();
  m_slash.destroy();
  m_ice.destroy();
}
