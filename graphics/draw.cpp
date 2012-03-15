#include "draw.hpp"
#include "../platform.hpp"      // for OpenGL/GLES functions
#include "../wjd_math.hpp"      // for trigonometry

#include <iostream>

void draw::line(V2f start, V2f end, Colour c, float thickness)
{
    // Start up
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(thickness);
    glColor4f(c.r, c.g, c.b, c.a);
    glEnable(GL_LINE_SMOOTH);

    // Specify points to draw
    GLfloat points[4]  = { (GLfloat)start.x, (GLfloat)start.y,
                            (GLfloat)end.x,  (GLfloat)end.y};

    // Draw them
    glVertexPointer(2, GL_FLOAT, 0, points);
    glDrawArrays(GL_LINES, 0, 2);

    // Shut down
    glDisable(GL_LINE_SMOOTH);
    glColor4f(1, 1, 1, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
}

void draw::line_loop(V2f points[], unsigned int n, Colour c, float thickness)
{
    // Start up
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(thickness);
    glColor4f(c.r, c.g, c.b, c.a);
    glEnable(GL_LINE_SMOOTH);

    // Specify points to draw
    GLfloat* loop = new GLfloat[2*n];
    for(unsigned int i = 0; i < n; i++)
    {
      loop[2*i] = points[i].x;
      loop[2*i + 1] = points[i].y;
    }

    // Draw them
    glVertexPointer(2, GL_FLOAT, 0, loop);
    glDrawArrays(GL_LINE_STRIP, 0, n);

    // Shut down
    glDisable(GL_LINE_SMOOTH);
    glColor4f(1, 1, 1, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
}

void draw::circle(V2f position, double radius, Colour c, bool fill)
{
    // Start up
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(c.r, c.g, c.b, c.a);

    // Specify points to draw
    GLfloat polygon[2*CIRCLE_N_SEGMENTS];

    for(int i = 0; i < CIRCLE_N_SEGMENTS; i++)
    {
        double radians = i*(2*PI)/CIRCLE_N_SEGMENTS;
        polygon[2*i] = position.x + cos(radians)*radius;
        polygon[2*i + 1] = position.y + sin(radians)*radius;
    }

    // Draw them
    glVertexPointer(2, GL_FLOAT, 0, polygon);
    // Fill circle, or not
    if(fill)
        glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_N_SEGMENTS);
    else
        glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_N_SEGMENTS);

    // Shut down
    glColor4f(1, 1, 1, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
}

