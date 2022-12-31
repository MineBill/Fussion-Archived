#include "Game.hpp"
#include <Fussion/Events/ApplicationEvents.hpp>
#include <Fussion/Window.hpp>
#include <iostream>

void Game::OnInitialize() {
    count++;
}

void Game::OnUpdate(f32) {
}

void Game::OnEvent(Ref<fsn::Event> event) {
    fsn::Dispatcher dispatcher(event);
    dispatcher.DispatchNoConsume<fsn::WindowResized>([](Ref<fsn::WindowResized> window_resized) {
        std::cout << window_resized->ToString() << '\n';
    });
}