#pragma once

struct BoundingBox final {
    vec2 start{}, end{};

    BoundingBox();
    BoundingBox(vec2 t_start, vec2 t_end);

    /// Expand the box to include point
    /// \param point
    void include(vec2 point);

    bool has_point(vec2 point) const;
};
