#include <Fussion/Math/Math.h>

namespace Fussion::Math
{
    f32 sign(f32 num)
    {
        if (num < 0)
            return -1;
        return 1;
    }

    f32 move_towards(f32 current, f32 target, f32 max_delta)
    {
        f32 difference = target - current;
        if (std::abs(difference) <= max_delta)
            return target;
        return current + sign(difference) * max_delta;
    }
} // namespace Fussion::Math
