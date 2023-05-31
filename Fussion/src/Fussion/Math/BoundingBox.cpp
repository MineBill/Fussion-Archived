#include "BoundingBox.h"
#include <Fussion/Core/Core.h>

BoundingBox::BoundingBox() = default;

BoundingBox::BoundingBox(vec2 t_start, vec2 t_end):start(t_start), end(t_end) {
    FSN_ASSERT(start.x <= end.x, "Start.x must be smaller than end.x");
    FSN_ASSERT(start.y <= end.y, "Start.y must be smaller than end.y");
}

void BoundingBox::include(vec2 point) {
    if (point.x < start.x) {
        start.x = point.x;
    }else if (point.x > end.x) {
        end.x = point.x;
    }
    if (point.y < start.y) {
        start.y = point.y;
    }else if (point.y > end.y) {
        end.y = point.y;
    }
}

bool BoundingBox::has_point(vec2 point) const {
    return point.x >= start.x && point.x <= end.x && point.y >= start.y && point.y <= end.y;
}
