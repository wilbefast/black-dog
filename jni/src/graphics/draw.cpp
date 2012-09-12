/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "draw.hpp"
#include "../global.hpp"              // for scale
#include "../platform.hpp"            // for OpenGL/GLES functions
#include "../math/wjd_math.hpp"       // for trigonometry

#include <iostream>

void draw::rectangle(fRect rect, Colour c)
{
  // Specify coordinates to draw
  GLfloat points[8] = { rect.x, rect.y,
                      rect.x, rect.y+rect.h,
                      rect.x+rect.w, rect.y,
                      rect.x+rect.w, rect.y+rect.h };

  // Start up
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor4f(c.r, c.g, c.b, c.a);

  // Draw points
  glVertexPointer(2, GL_FLOAT, 0, points);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Shut down
  glColor4f(1, 1, 1, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();
}

void draw::line(V2f start, V2f end, Colour c, float thickness)
{
    // Specify coordinates to draw
    GLfloat points[4]  = { (GLfloat)start.x, (GLfloat)start.y,
                            (GLfloat)end.x,  (GLfloat)end.y};

    // Start up
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(thickness);
    glColor4f(c.r, c.g, c.b, c.a);
    glEnable(GL_LINE_SMOOTH);
    glScalef(global::scale.x, global::scale.y, 0.0f);

    // Draw points
    glVertexPointer(2, GL_FLOAT, 0, points);
    glDrawArrays(GL_LINES, 0, 2);

    // Shut down
    glDisable(GL_LINE_SMOOTH);
    glColor4f(1, 1, 1, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
}

void draw::line_loop(V2f points[], unsigned int n_pts, Colour c, float thickness)
{
    // Specify coordinates to draw
    GLfloat* loop = new GLfloat[2*n_pts];
    for(unsigned int i = 0; i < n_pts; i++)
    {
      loop[2*i] = points[i].x;
      loop[2*i + 1] = points[i].y;
    }

    // Start up
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(thickness);
    glColor4f(c.r, c.g, c.b, c.a);
    glEnable(GL_LINE_SMOOTH);
    glScalef(global::scale.x, global::scale.y, 0.0f);

    // Draw points
    glVertexPointer(2, GL_FLOAT, 0, loop);
    glDrawArrays(GL_LINE_STRIP, 0, n_pts);

    // Shut down
    glDisable(GL_LINE_SMOOTH);
    glColor4f(1, 1, 1, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
}

void draw::height_line(float height[], unsigned int n_pts, float x_spacing,
                      V2f base, unsigned int head_i, Colour c, float thickness)
{
  // Specify coordinates to draw
  GLfloat* vertices = new GLfloat[n_pts*2];
  // vertex index keeps track of position in vertices array
  int v_i = 0;
  // x keeps track of the position on the screen
  float x = base.x;
  // i keeps track of the position in the height-map (circular array)
  for(unsigned int i = (head_i+1)%n_pts; i != head_i; i = (i+1)%n_pts)
  {
    // store x
    vertices[v_i++] = x;
    x += x_spacing;
    // store y
    vertices[v_i++] = height[i];
  }
  vertices[v_i++] = x;
  vertices[v_i++] = height[head_i];

  // Start up
  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(thickness);
  glColor4f(c.r, c.g, c.b, c.a);
  glEnable(GL_LINE_SMOOTH);
  glScalef(global::scale.x, global::scale.y, 0.0f);

  // Draw points
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glDrawArrays(GL_LINE_STRIP, 0, n_pts);

  // Shut down
  glDisable(GL_LINE_SMOOTH);
  glColor4f(1, 1, 1, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();

  /// Remember to free the memory allocated !
  delete[] vertices;
}

void draw::height_fill(float height[], unsigned int n_pts, float x_spacing,
                      V2f base, unsigned int head_i, Colour c)
{
  // are we drawing the roof or the floor?
  bool roof = base.y < height[head_i];

  // Specify the coordinates to draw
  // we'll need 1 quad and 1 triangle per point (except the last point)
  // in total that's 3 triangles, 18 vertices per point (except the last point)
  GLfloat* vertices = new GLfloat[18*(n_pts-1)];
  // vertex index keeps track of position in vertices array
  int v_i = 0;
  // x keeps track of the position on the screen
  float x = base.x;
  // i keeps track of the position in the height-map (circular array)
  for(unsigned int i = (head_i+1)%n_pts; i != head_i; i = (i+1)%n_pts)
  {
    // local variables
    unsigned int next_i = (i+1)%n_pts;
    unsigned int lower_i, higher_i;
    float next_x = x+x_spacing, x_of_higher, x_of_lower;
    bool descending = (height[i] < height[next_i]);
    if((roof && descending) || (!roof && !descending) )
    {
      lower_i = i;
      x_of_lower = x;
      higher_i = next_i;
      x_of_higher = next_x;
    }
    else
    {
      lower_i = next_i;
      x_of_lower = next_x;
      higher_i = i;
      x_of_higher = x;
    }

    /// QUAD, triangle 1
    // triangle 1, point 1
    vertices[v_i++] = x;                // x
    vertices[v_i++] = base.y;           // y
    // triangle 1, point 2
    vertices[v_i++] = next_x;           // x
    vertices[v_i++] = base.y;           // y
    // triangle 1, point 3
    vertices[v_i++] = x;                // x
    vertices[v_i++] = height[lower_i];  // y

    /// QUAD, triangle 2
    // triangle 2, point 1
    vertices[v_i++] = next_x;           // x
    vertices[v_i++] = base.y;           // y
    // triangle 2, point 2
    vertices[v_i++] = x;                // x
    vertices[v_i++] = height[lower_i];  // y
    // triangle 2, point 3
    vertices[v_i++] = next_x;           // x
    vertices[v_i++] = height[lower_i];  // y

    /// BOTTOM, triangle 3
    // triangle 3, point 1
    vertices[v_i++] = x_of_lower;           // x
    vertices[v_i++] = height[lower_i];      // y
    // triangle 3, point 2
    vertices[v_i++] = x_of_higher;          // x
    vertices[v_i++] = height[lower_i];      // y
    // triangle 3, point 3
    vertices[v_i++] = x_of_higher;           // x
    vertices[v_i++] = height[higher_i];      // y

    /// REMEMBER TO MOVE X
    x += x_spacing;
  }

  // Start up
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor4f(c.r, c.g, c.b, c.a);

  // Draw points
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  // Unfortunately there is no way we can use FAN or STRIP here or I would !
  glDrawArrays(GL_TRIANGLES, 0, 9*(n_pts-1));

  // Shut down
  glColor4f(1, 1, 1, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();

  /// Remember to free the memory allocated !
  delete vertices;
}

void draw::circle(V2f position, double radius, Colour c, bool fill)
{
    // Specify coordinates to draw
    GLfloat polygon[2*CIRCLE_N_SEGMENTS];

    for(int i = 0; i < CIRCLE_N_SEGMENTS; i++)
    {
        double radians = i*(2*PI)/CIRCLE_N_SEGMENTS;
        polygon[2*i] = position.x + cos(radians)*radius;
        polygon[2*i + 1] = position.y + sin(radians)*radius;
    }

    // Start up
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(c.r, c.g, c.b, c.a);
    glEnable(GL_LINE_SMOOTH);

    // Draw points
    glVertexPointer(2, GL_FLOAT, 0, polygon);
    // Fill circle, or not
    if(fill)
        glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_N_SEGMENTS);
    else
        glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_N_SEGMENTS);

    // Shut down
    glDisable(GL_LINE_SMOOTH);
    glColor4f(1, 1, 1, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
}

