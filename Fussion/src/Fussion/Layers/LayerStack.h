#pragma once
#include "Layer.h"

namespace Fussion
{
    /*
     * Simple wrapper around std::vector to allow reverse iterating
     */
    class LayerStack
    {
        std::vector<Ref<Layer>> m_layers{};

        std::vector<Ref<Layer>> m_overlays{};

    public:
        template<std::derived_from<Layer> T, typename... Args>
        Ref<T> push_layer(Args &&...args)
        {
            auto layer = std::make_shared<T>(std::forward<Args>(args)...);
            layer->on_load();
            m_layers.push_back(layer);
            return layer;
        }

        template<std::derived_from<Layer> T, typename... Args>
        Ref<T> push_overlay(Args &&...args)
        {
            auto layer = std::make_shared<T>(std::forward<Args>(args)...);
            layer->on_load();
            m_layers.push_back(layer);
            return layer;
        }

        mustuse const std::vector<Ref<Layer>> &overlays() const
        {
            return m_overlays;
        }

        auto begin()
        {
            return std::reverse_iterator(m_layers.end());
        }
        auto end()
        {
            return std::reverse_iterator(m_layers.begin());
        }
    };
} // namespace Fussion