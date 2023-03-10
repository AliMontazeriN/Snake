#ifndef GAME_H
#define GAME_H

#include <thread>
#include <future>
#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  std::thread Run(Controller &&controller, Renderer &&renderer,
           std::size_t target_frame_duration, std::promise<bool> &&prm);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  Snake movingObstacle;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::uniform_int_distribution<int> random_direction;

  int score{0};

  void PlaceFood();
  void Update();
  Snake::Direction GetRandomDirection();
  void checkForCollision(Snake &snake, Snake &movingObstacle);

};

#endif