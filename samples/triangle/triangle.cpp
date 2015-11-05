// Copyright 2015 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "fplbase/renderer.h"
#include "fplbase/mesh.h"
#include "fplbase/input.h"
#include <cassert>

// This is a sample that displays a colored quad.
//
// It demonstrates usage of:
// - fpl::Renderer to load shaders from strings and setup rendering.
// - fpl::Mesh for rendering simple geometry.
// - fpl::InputSystem to query for exit events and elapsed time.

extern "C" int FPL_main(int /*argc*/, char** /*argv*/) {
  fpl::Renderer renderer;
  fpl::InputSystem input;

  renderer.Initialize(mathfu::vec2i(800, 600), "Simple rendering test");
  input.Initialize();

  // A vertex shader that passes untransformed position thru.
  auto vertex_shader =
    "attribute vec4 aPosition;\n"
    "void main() { gl_Position = aPosition; }\n";

  // A fragment shader that outputs a green pixel.
  auto fragment_shader =
    "void main() { gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); }\n";

  auto shader = renderer.CompileAndLinkShader(vertex_shader, fragment_shader);
  assert(shader);

  while (!(input.exit_requested() ||
           input.GetButton(fpl::FPLK_AC_BACK).went_down())) {
    renderer.AdvanceFrame(input.minimized(), input.Time());
    input.AdvanceFrame(&renderer.window_size());

    float color = (1.0f - cos(input.Time())) / 2.0f;
    renderer.ClearFrameBuffer(mathfu::vec4(color, 0.0f, color, 1.0f));

    shader->Set(renderer);

    // define geometry for a triangle
    const fpl::Attribute format[] = {
      fpl::Attribute::kPosition3f, fpl::Attribute::kEND
    };
    const unsigned short indices[] = { 0, 1, 2 };
    const float vertices[] = {
      -.5f, -.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
      0.5f, -.5f, 0.0f
    };

    fpl::Mesh::RenderArray(fpl::Mesh::Primitive::kTriangles, 3, format,
                           sizeof(float) * 3, vertices, indices);
  }

  renderer.ShutDown();
  return 0;
}
