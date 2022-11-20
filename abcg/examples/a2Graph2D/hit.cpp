#include "hit.hpp"

#include <glm/gtx/fast_trigonometry.hpp>

void Hit::create(GLuint program) {
  destroy();

  m_program = program;

  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  // m_scale = abcg::glGetUniformLocation(m_program, "scale");

  std::array positions{
      glm::vec2{-0.06f, -0.03f}, glm::vec2{-0.03f, +0.03f},
      glm::vec2{-0.03f, +0.01f}, glm::vec2{-0.02f, +0.07f},
      glm::vec2{+0.00f, +0.04f}, glm::vec2{+0.06f, +0.07f},
      glm::vec2{+0.03f, +0.00f}, glm::vec2{+0.09f, -0.08f},
      glm::vec2{-0.04f, -0.04f}, glm::vec2{-0.10f, -0.05f},
  };

  std::array const indices{0, 1, 2, 2, 3, 4, 0, 5, 6, 0, 6, 7, 0, 8, 9};

  for (auto &position : positions) {
    position *= glm::vec2{3.0f, 3.0f};
  }

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

void Hit::paint() {

  // void Hit::paint(const GameState &m_gameState) {
  // if (m_gameState != GameState::AttackAnimation)
  //   return;

  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);

  // abcg::glUniform1f(m_scale, );

  abcg::glUniform4fv(m_colorLoc, 1, &m_color.r);
  abcg::glDrawElements(GL_TRIANGLE_STRIP, 6 * 3, GL_UNSIGNED_INT, nullptr);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Hit::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}