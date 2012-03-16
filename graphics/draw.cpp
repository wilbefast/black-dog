#include "draw.hpp"
#include "../platform.hpp"      // for OpenGL/GLES functions
#include "../wjd_math.hpp"      // for trigonometry

#include <iostream>

void draw::line(V2f start, V2f end, Colour c, float thickness)
{
    // Specify points to draw
    GLfloat points[4]  = { (GLfloat)start.x, (GLfloat)start.y,
                            (GLfloat)end.x,  (GLfloat)end.y};

    // Start up
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(thickness);
    glColor4f(c.r, c.g, c.b, c.a);
    glEnable(GL_LINE_SMOOTH);

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
    // Specify points to draw
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
  // Specify points to draw
  GLfloat* result = new GLfloat[n_pts*2];
  // result i keeps track of position in result array
  int r_i = 0;
  // x keeps track of the position on the screen
  float x = base.x;
  // i keeps track of the position in the height-map (circular array)
  for(unsigned int i = (head_i+1)%n_pts; i != head_i; i = (i+1)%n_pts)
  {
    // store x
    result[r_i++] = x;
    x += x_spacing;
    // store y
    result[r_i++] = height[i];
  }
  result[r_i++] = x;
  result[r_i++] = height[head_i];

  // Start up
  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(thickness);
  glColor4f(c.r, c.g, c.b, c.a);
  glEnable(GL_LINE_SMOOTH);

  // Draw points
  glVertexPointer(2, GL_FLOAT, 0, result);
  glDrawArrays(GL_LINE_STRIP, 0, n_pts);

  // Shut down
  glDisable(GL_LINE_SMOOTH);
  glColor4f(1, 1, 1, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();

  /// Remember to free the memory allocated !
  delete result;
}

void draw::height_fill(float height[], unsigned int n_pts, float x_spacing,
                      V2f base, unsigned int head_i, Colour c)
{
  // Specify points to draw
  GLfloat* result = new GLfloat[18*n_pts];
  // result i keeps track of position in result array
  int r_i = 0;
  // x keeps track of the position on the screen
  float x = base.x;
  // i keeps track of the position in the height-map (circular array)
  for(unsigned int i = (head_i+1)%n_pts; i != head_i; i = (i+1)%n_pts)
  {
    // local variables
    unsigned int next_i = (i+1)%n_pts;
    unsigned int lower_i, higher_i;
    float next_x = x+x_spacing, x_of_higher, x_of_lower;
    if(height[i] < height[next_i])
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
    result[r_i++] = x;                // x
    result[r_i++] = base.y;           // y
    // triangle 1, point 2
    result[r_i++] = next_x;           // x
    result[r_i++] = base.y;           // y
    // triangle 1, point 3
    result[r_i++] = x;                // x
    result[r_i++] = height[lower_i];  // y

    /// QUAD, triangle 2
    // triangle 2, point 1
    result[r_i++] = next_x;           // x
    result[r_i++] = base.y;           // y
    // triangle 2, point 2
    result[r_i++] = x;                // x
    result[r_i++] = height[lower_i];  // y
    // triangle 2, point 3
    result[r_i++] = next_x;           // x
    result[r_i++] = height[lower_i];  // y

    /// BOTTOM, triangle 3
    // triangle 3, point 1
    result[r_i++] = x_of_lower;           // x
    result[r_i++] = height[lower_i];      // y
    // triangle 3, point 2
    result[r_i++] = x_of_higher;          // x
    result[r_i++] = height[lower_i];      // y
    // triangle 3, point 3
    result[r_i++] = x_of_higher;           // x
    result[r_i++] = height[higher_i];      // y

    /// REMEMBER TO MOVE X
    x += x_spacing;
  }

  // Start up
  glEnableClientState(GL_VERTEX_ARRAY);
  c.g = c.b = 0;
  glColor4f(c.r, c.g, c.b, c.a);

  // Draw points
  glVertexPointer(2, GL_FLOAT, 0, result);
  // Unfortunately there is no way we can use FAN or STRIP here or I would !
  glDrawArrays(GL_TRIANGLES, 0, 9*n_pts);

  // Shut down
  glColor4f(1, 1, 1, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();

  /// Remember to free the memory allocated !
  //delete result;
}

void draw::circle(V2f position, double radius, Colour c, bool fill)
{
    // Specify points to draw
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

