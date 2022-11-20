#ifndef WINDOW_HPP_
#define WINDOW_HPP_
/*
#include <random>

#include "abcgOpenGL.hpp"

//#include file

//#include "hit.hpp"
//#include "ice.hpp"
#include "slash.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaint() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_effectsProgram{};

  abcg::Timer m_waitingTime;

  std::default_random_engine m_randomEngine{};

  // Hit m_hit;
  Slash m_slash;
  // Ice m_ice;

  void restart();
};
*/

#include <random>

#include "abcgOpenGL.hpp"

//#include "asteroids.hpp"
//#include "bullets.hpp"
#include "slash.hpp"
//#include "starlayers.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  // void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_objectsProgram{};

  enum class State { Idle, AttackAnimation };

  State m_state{State::Idle};

  Slash m_slash;

  abcg::Timer m_restartWaitTimer;

  ImFont *m_font{};

  std::default_random_engine m_randomEngine;

  void restart();
};

#endif