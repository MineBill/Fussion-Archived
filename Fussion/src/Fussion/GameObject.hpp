#pragma once
#include "Fussion/Components/IComponent.hpp"
#include "Types.hpp"
#include <vector>

namespace fussion
{

class GameObject
{
    String name {};
    std::vector<Ptr<IComponent>> m_components {};

    GameObject() = default;

public:
    template<std::derived_from<IComponent> C, typename... Args>
    void AddComponent(Args &&...args)
    {
        auto component = std::make_unique<C>(std::forward<Args>(args)...);

        component->OnLoad();

        m_components.push_back(std::move(component));
    }
};

}