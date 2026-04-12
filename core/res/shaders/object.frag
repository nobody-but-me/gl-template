#version 330 core

in vec2 texture_coords;
out vec4 frag_colour;

uniform sampler2D object_texture;
uniform bool is_textured;
uniform bool is_animated;

uniform bool circle=false;

uniform int columns;
uniform int rows;

uniform vec4 colour;
uniform int index;

void main() {
  if(circle)
  {
    vec2 centered_coords=texture_coords-vec2(0.5, 0.5);
    
    float current_radius=length(centered_coords);
    float signed_distance=current_radius-0.4f;
    
    float _width=fwidth(signed_distance);
    float alpha=colour.a-smoothstep(_width*-1.0f,_width,signed_distance);
    
    /*
    /// normal circle with anti-alising
    float _width=fwidth(signed_distance);
    float alpha=colour.a-smoothstep(_width*-1.0f,_width,signed_distance);
    
    /// flashlight-like circle
    float _width=.1f;
    float alpha=colour.a-smoothstep(_width*-1.0f,_width,signed_distance);
    
    /// circle without anti-alising
    float _width=fwidth(signed_distance);
    float alpha=colour.a-smoothstep(_width*1.0f,_width,signed_distance);
    */
    
    if (is_textured) {
      frag_colour = vec4(colour.rgb,alpha) * texture(object_texture, texture_coords);
    } else {
      frag_colour = vec4(0.0f,1.0f,0.0f, alpha);
    }
    return;
  }
  
  vec2 pos = vec2(index % int(columns), int(index / columns) * -1);
  
  if (is_textured) {
    if (!is_animated) frag_colour = colour * texture(object_texture, texture_coords);
    else              frag_colour = colour * texture(object_texture, vec2((texture_coords.x / columns) + pos.x * (1.0f / columns), (texture_coords.y / rows) + pos.y * (1.0f / rows)));
  } else {
      frag_colour = colour;
  }
}
