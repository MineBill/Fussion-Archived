#include "Game.hpp"
#include <Fussion/Window.hpp>
#include <iostream>

void Game::OnInitialize() {
    count++;
}

void Game::OnUpdate(f32 delta) {
    std::cout << "ElapsedTime: " << delta << '\n';
}

void Game::OnEvent() {
}