#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

enum class State { Playing, GameOver, Win };

struct GameData {
  State m_state{State::Playing};
};

#endif