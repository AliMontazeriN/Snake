#include <iostream>
#include <thread>
#include <future>
#include <memory>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  //std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //std::unique_ptr<Controller> controller = std::make_unique<Controller>();
  //std::shared_ptr<Game> game;
  //game = std::make_unique<Game>(kGridWidth, kGridHeight);
  std::promise<bool> promise;
  std::future<bool> future = promise.get_future();
  std::thread tGame = game.Run(std::move(controller), std::move(renderer), kMsPerFrame, std::move(promise));
  //std::thread tGame = std::thread(&Game::Run, game, std::move(controller), std::move(renderer), kMsPerFrame);
  //std::future<void> ftr = std::async(std::launch::async, &Game::Run, game, std::move(controller), std::move(renderer), kMsPerFrame);
  if(future.get())
  {
    std::cout << "According to promise-future channel, the snake is: ALIVE" << std::endl;
  } else {
    std::cout << "According to promise-future channel, the snake is: DEAD" << std::endl;
  }
  if(tGame.joinable())
  {
    tGame.join();
  }
  //ftr.wait();
  // game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}

