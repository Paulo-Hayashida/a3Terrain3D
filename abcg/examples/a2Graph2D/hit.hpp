#ifndef HIT_HPP_
#define HIT_HPP_

#include "abcgOpenGL.hpp"
//#include "gamestate.hpp"

class Hit {
public:
  void create(GLuint program);
  void paint();
  // void paint(GameState const &m_gameState);
  void destroy();

  glm::vec4 m_color{1};
  float m_scale{3.0f};

  abcg::Timer animationEffectTimer;

private:
  GLuint m_program{};
  GLuint m_colorLoc{};
  GLuint m_scaleLoc{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
};

#endif