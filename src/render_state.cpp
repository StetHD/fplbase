#include "precompiled.h"  // NOLINT

#include "fplbase/render_state.h"

namespace fplbase {

Viewport::Viewport() : position(mathfu::kZeros2i), size(mathfu::kZeros2i) {}

Viewport::Viewport(int x, int y, int width, int height) {
  position[0] = x;
  position[1] = y;

  size[0] = width;
  size[1] = height;
}

Viewport::Viewport(const mathfu::vec2i &pos, const mathfu::vec2i &size)
    : position(pos), size(size) {}

bool operator==(const Viewport &vp1, const Viewport &vp2) {
  return (vp1.position == vp2.position && vp1.size == vp2.size);
}

bool operator!=(const Viewport &vp1, const Viewport &vp2) {
  return !(vp1 == vp2);
}

}  // namespace fplbase