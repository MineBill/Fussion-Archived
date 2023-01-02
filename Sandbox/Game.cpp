#include "Game.hpp"
#include "CubeData.hpp"
#include <Fussion/Events/ApplicationEvents.hpp>
#include <Fussion/Window.hpp>
#include <iostream>

void Game::on_initialize() {
    va = fussion::VertexArray::create(CUBE_DATA, { fussion::VertexType::Vector3, fussion::VertexType::Vector2, fussion::VertexType::Vector3 });
}

void Game::on_update(f32) {
    va->use();
}

void Game::on_event(Ref<fsn::Event> event) {
    fsn::Dispatcher dispatcher(event);
    dispatcher.dispatch_no_consume<fsn::WindowResized>([](const Ref<fsn::WindowResized>& window_resized) {
        std::cout << window_resized->to_string() << '\n';
    });
}