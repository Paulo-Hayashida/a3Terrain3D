#include "window.hpp"

void Window::onCreate() {}

void Window::onPaintUI() {
  // abcg::OpenGLWindow::onPaintUI();
  {
    // Setagem do tamanho da janela
    ImGui::SetNextWindowSize(ImVec2(600, 300));

    // Setagem da posição inicial da janela
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    // Inicia a janela com o devido titulo
    ImGui::Begin("Atividade 1 - Calculadora");

    // Declaração das variaveis que serão usadas
    const char *op[] = {"+", "-", "*", "/", "^", "Eq Linear", "Eq Quadrada"};
    static int op_now = 0;
    static float val1{};
    static float val2{};
    static float a{};
    static float b{};
    static float c{};
    static float x1{};
    static float x2{};
    static float ans{};
    static bool clicked = false;

    // Combo box selecione op
    ImGui::Combo("Selecione a op", &op_now, op, IM_ARRAYSIZE(op));

    // Switch que fala o que cada valor selecionado no combo box faz
    switch (op_now) {

    // op +
    case 0:
      // Caixas para inserção de valores a serem calculados
      ImGui::InputFloat("Digite o primeiro valor", &val1);
      ImGui::InputFloat("Digite o segundo valor", &val2);
      ans = val1 + val2;

      // Botão para mostrar as respostas
      if (ImGui::Button("Calcular")) {
        clicked = true;
      }

      // Teste para saber se foi clicado
      if (clicked)
        ImGui::Text("Resposta = %f", ans);
      break;

    // As operações abaixo tem uma estrutura similar a soma
    // op -
    case 1:
      ImGui::InputFloat("Digite o primeiro valor", &val1);
      ImGui::InputFloat("Digite o segundo valor", &val2);
      ans = val1 - val2;
      if (ImGui::Button("Calcular")) {
        clicked = true;
      }
      if (clicked)
        ImGui::Text("Resposta = %f", ans);
      break;

    // op *
    case 2:
      ImGui::InputFloat("Digite o primeiro valor", &val1);
      ImGui::InputFloat("Digite o segundo valor", &val2);
      ans = val1 * val2;
      if (ImGui::Button("Calcular")) {
        clicked = true;
      }
      if (clicked)
        ImGui::Text("Resposta = %f", ans);
      break;

    // op /
    case 3:
      ImGui::InputFloat("Digite o primeiro valor", &val1);
      ImGui::InputFloat("Digite o segundo valor", &val2);
      ans = val1 / val2;
      if (ImGui::Button("Calcular")) {
        clicked = true;
      }
      if (clicked)
        ImGui::Text("Resposta = %f", ans);
      break;

    // op ^
    case 4:
      ImGui::InputFloat("Digite o primeiro valor", &val1);
      ImGui::InputFloat("Digite o segundo valor", &val2);
      ans = pow(val1, val2);
      if (ImGui::Button("Calcular")) {
        clicked = true;
      }
      if (clicked)
        ImGui::Text("Resposta = %f", ans);
      break;

    // op linear equation
    case 5:
      ImGui::Text("Equação na forma a*x + b");
      ImGui::InputFloat("Digite o valor de a", &a);
      ImGui::InputFloat("Digite o valor de b", &b);
      x1 = (-b) / a;
      if (ImGui::Button("Calcular")) {
        clicked = true;
      }
      if (clicked)
        ImGui::Text("x = %f", x1);

      // Variaveis locais para função adicional
      static float f{};
      static bool check = false;

      // Função adicional feita para a operação equação linear apenas
      ImGui::Checkbox("Selecione para exibir mais funções", &check);
      if (check) {
        ImGui::Text("Varie o valor de a para saber a inclinação da reta");
        // Slider da função adicional
        ImGui::SliderFloat("Valor de a", &f, -1.0f, 1.0f);
        if (f > 0) {
          ImGui::Text("Inclinação positiva");
        } else if (f < 0) {
          ImGui::Text("Inclinação negativa");
        } else {
          ImGui::Text("Função Constante");
        }
      }
      break;

    // op quadratic equation
    case 6:
      ImGui::Text("Equação na forma a*x^2 + b*x + c");
      ImGui::InputFloat("Digite o valor de a", &a);
      ImGui::InputFloat("Digite o valor de b", &b);
      ImGui::InputFloat("Digite o valor de c", &c);
      float delta = b * b - (4 * a * c);
      x1 = (-b - sqrt(delta)) / (2 * a);
      x2 = (-b + sqrt(delta)) / (2 * a);
      if (ImGui::Button("Calcular")) {
        clicked = true;
      }
      if (clicked)
        ImGui::Text("x1 = %f x2 = %f", x1, x2);
      break;
    }

    // ImGui::AlignTextToFramePadding();

    ImGui::End();
  }
}