#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#define mustuse [[nodiscard]]

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

namespace Fussion
{
    using String = std::string;
    using StringView = std::string_view;

    template<typename T>
    using Optional = std::optional<T>;
    template<typename T>
    using OptionalRef = Optional<std::reference_wrapper<T>>;

    template<typename T>
    using Ptr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    Ptr<T> make_ptr(Args &&...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename... Args>
    Ref<T> make_ref(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    using WeakRef = std::weak_ptr<T>;
} // namespace Fussion
