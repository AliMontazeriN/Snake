#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include<memory>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(std::make_unique<float>(grid_width / 2)),
        head_y(std::make_unique<float>(grid_height / 2)) {}

  // rule of five
  ~Snake(){}; //destructor

  Snake (const Snake &source) //copy constructor
  {
    head_x = std::make_unique<float>(*source.head_x);
    head_y = std::make_unique<float>(*source.head_y);
    //body = std::vector<std::make_unique<SDL_Point>()>;
    body = source.body;
  };

  Snake &operator=(const Snake &source) //copy assignment operator
  {
    if(this == &source)
      return *this;
    
    head_x = std::make_unique<float>(*source.head_x);
    head_y = std::make_unique<float>(*source.head_y);
    //body = std::vector<std::make_unique<SDL_Point>()>;
    body = source.body;
    return *this;
  }

  Snake (const Snake &&source) //move constructor
  {
    head_x = std::make_unique<float>(*source.head_x);
    head_y = std::make_unique<float>(*source.head_y);
    body = source.body;

  };

  Snake &operator=(const Snake &&source) //move assignment operator
  {
    if(this == &source)
      return *this;
    
    head_x = std::make_unique<float>(*source.head_x);
    head_y = std::make_unique<float>(*source.head_y);
    body = source.body;

    return *this;
  }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;
  bool directionChange = false;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  std::shared_ptr<float> head_x = nullptr;
  std::shared_ptr<float> head_y = nullptr;
  std::vector<std::shared_ptr<SDL_Point>> body;

 private:
  void UpdateHead();
  void UpdateBody(std::shared_ptr<SDL_Point> &&current_cell, std::shared_ptr<SDL_Point> &&prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif