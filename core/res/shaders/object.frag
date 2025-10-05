#version 330 core

in vec2 texture_coords;
out vec4 frag_colour;

uniform sampler2D object_texture;
uniform bool is_textured;
uniform vec4 colour;

void main() {
  if (is_textured) {
    frag_colour = colour * texture(object_texture, texture_coords);
  } else {
    frag_colour = colour;
  }
}
