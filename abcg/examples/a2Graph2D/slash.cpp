#include "slash.hpp"

#include <glm/gtx/fast_trigonometry.hpp>

void Slash::create(GLuint program) {
  destroy();

  m_program = program;

  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  // m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");

  std::array positions{
      glm::vec2{+0.15f, +0.20f}, glm::vec2{+0.04f, +0.22f},
      glm::vec2{+0.06f, +0.16f}, glm::vec2{-0.04f, +0.14f},
      glm::vec2{+0.03f, +0.12f}, glm::vec2{-0.08f, +0.10f},
      glm::vec2{-0.01f, +0.06f}, glm::vec2{-0.14f, +0.03f},
      glm::vec2{-0.03f, -0.02f}, glm::vec2{-0.14f, -0.08f},
      glm::vec2{-0.01f, -0.10f}, glm::vec2{-0.04f, -0.19f},
      glm::vec2{+0.04f, -0.16f}, glm::vec2{+0.09f, -0.22f},
  };

  std::array const indices{0,  1, 2,  1,  2,  3,  2,  3,  4,  3,  4,  5,  4,
                           5,  6, 5,  6,  7,  6,  7,  8,  7,  8,  9,  8,  9,
                           10, 9, 10, 11, 10, 11, 12, 11, 12, 13, 12, 13, 14};

  for (auto &position : positions) {
    position *= glm::vec2{2.0f, 2.0f};
  }

  // Generate VBO

  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  /*
  // Generate VBO Position
  abcg::glGenBuffers(1, &m_VBOP);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOP);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  std::vector<glm::vec4> color{{1,1,1,1}};

  //Generate VBO Color
  abcg::glGenBuffers(1, &m_VBOC);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOC);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(color), color.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  */

  // Generate EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  GLint positionAttributes{abcg::glGetAttribLocation(m_program, "inPosition")};
  // GLint colorAttributes{abcg::glGetAttribLocation(m_program, "inColor")};
  //   Create VAO

  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttributes);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Teste com inColor
  /*
  abcg::glEnableVertexAttribArray(positionAttributes);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOP);
  abcg::glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glEnableVertexAttribArray(positionAttributes);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOC);
  abcg::glVertexAttribPointer(colorAttributes, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  */

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Slash::paint() {

  // void Slash::paint(const GameState &m_gameState) {
  // if (m_gameState != GameState::AttackAnimation)
  //   return;

  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);

  // abcg::glUniform1f(m_scale, );

  abcg::glUniform4fv(m_colorLoc, 1, &m_color.r);

  /*
  if (animationEffectTimer.elapsed() > 2)
    animationEffectTimer.restart();

  if (animationEffectTimer.elapsed() > 1) {
    abcg::glClearColor(0, 0, 0, 1);
  }
  */

  abcg::glDrawElements(GL_TRIANGLE_STRIP, 12 * 3, GL_UNSIGNED_INT, nullptr);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Slash::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);

  /*
  abcg::glDeleteBuffers(1, &m_VBOP);
  abcg::glDeleteBuffers(1, &m_VBOC);
  */
}

/*
if (animationEffectTimer.elapsed() > 100.0 / 1000.0)
animationEffectTimer.restart();

if (animationEffectTimer < 50.0 / 1000.0) {
  abcg::glClearColor(0, 0, 0, 1);
}
*/