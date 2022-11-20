#include "ice.hpp"

#include <glm/gtx/fast_trigonometry.hpp>

void Ice::create(GLuint program) {
  destroy();

  m_program = program;

  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  // m_scale = abcg::glGetUniformLocation(m_program, "scale");

  std::array positions{
      glm::vec2{+0.00f, +0.27f}, glm::vec2{+0.20f, +0.12f},
      glm::vec2{+0.00f, +0.21f}, glm::vec2{+0.15f, +0.10f},
      glm::vec2{+0.15f, -0.10f}, glm::vec2{+0.20f, -0.12f},
      glm::vec2{+0.00f, -0.21f}, glm::vec2{+0.00f, -0.27f},
      glm::vec2{-0.10f, -0.15f}, glm::vec2{-0.20f, -0.12f},
      glm::vec2{-0.15f, +0.10f}, glm::vec2{-0.20f, +0.12f},
  };

  std::array const indices{0, 1, 2, 1, 3, 2, 1, 4, 3, 1, 5, 4, 4, 5, 6, 5, 7, 6,
                           6, 7, 8, 7, 9, 8, 8, 9, 10, 9, 11, 10, 11, 0, 2,
                           // Hexagono interno
                           9, 11, 10, 2, 3, 10, 3, 8, 10, 3, 4, 8, 4, 6, 8};

  for (auto &position : positions) {
    position *= glm::vec2{2.0f, 2.0f};
  }

  // tentando fazer o Hexagono interno separado
  /*
  std::array positions{
      glm::vec2{+0.00f, +0.27f}, glm::vec2{+0.20f, +0.12f},
      glm::vec2{+0.00f, +0.21f}, glm::vec2{+0.15f, +0.10f},
      glm::vec2{+0.15f, -0.10f}, glm::vec2{+0.20f, -0.12f},
      glm::vec2{+0.00f, -0.21f}, glm::vec2{+0.00f, -0.27f},
      glm::vec2{-0.10f, -0.15f}, glm::vec2{-0.20f, -0.12f},
      glm::vec2{-0.15f, +0.10f}, glm::vec2{-0.20f, +0.12f},
  };

  std::array const indices{0, 1, 2, 1, 3, 2, 1, 4, 3, 1, 5, 4, 4, 5, 6, 5, 7, 6,
                           6, 7, 8, 7, 9, 8, 8, 9, 10, 9, 11, 10,
                           // Hexagono interno
                           9, 11, 10, 2, 3, 10, 3, 8, 10, 3, 4, 8, 4, 6, 8};

  for (auto &position : positions) {
    position *= glm::vec2{2.0f, 2.0f};
  }
  */

  // Generate VBO

  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  GLint positionAttributes{abcg::glGetAttribLocation(m_program, "inPosition")};
  // auto const colorAttribute{abcg::glGetAttribLocation(m_program, "inColor")};
  //  Create VAO

  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttributes);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Ice::paint() {

  // void Ice::paint(const GameState &m_gameState) {
  // if (m_gameState != GameState::AttackAnimation)
  //   return;

  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);

  // abcg::glUniform1f(m_scale, );

  abcg::glUniform4fv(m_colorLoc, 1, &m_color.r);
  abcg::glDrawElements(GL_TRIANGLE_STRIP, 16 * 3, GL_UNSIGNED_INT, nullptr);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Ice::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}