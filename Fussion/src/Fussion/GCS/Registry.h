#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/GCS/GameObject.h"

namespace Fussion
{
    class Registry
    {
        std::vector<Ref<GameObject>> m_gameObjects{};
        bool m_initialized{false};

        Ref<GameObject> m_root{};

    public:
        Registry();

        Ref<GameObject> Create(StringView name, const Ref<GameObject> &parent = nullptr);

        void Update(f32);

        void OnEvent(Event &);

        const std::vector<Ref<GameObject>> GetAllGameObjects() const
        {
            return m_gameObjects;
        }

        Ref<GameObject> &GetRoot()
        {
            return m_root;
        }

        /* struct Iterator {
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = int;
            using pointer = int *;   // or also value_type*
            using reference = int &; // or also value_type&

            Iterator(pointer p) : m_ptr(p)
            {
            }

        private:
            pointer m_ptr{};
        }; */
    };
} // namespace Fussion
