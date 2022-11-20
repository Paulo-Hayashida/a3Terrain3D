#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"

//#include file

#include "hit.hpp"
#include "ice.hpp"
#include "slash.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_effectsProgram{};

  enum class GameState { Idle, AttackAnimation };
  GameState m_gameState{GameState::Idle};

  abcg::Timer m_waitingTime;

  std::default_random_engine m_randomEngine{};

  int m_atktype{0};

  Hit m_hit;
  Slash m_slash;
  Ice m_ice;

  void restart();
};

#endif