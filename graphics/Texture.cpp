#include "Texture.hpp"

#include "SDL.h"            // Needed for IMG_Load
#include "SDL_image.h"

#include "../global.hpp"       // Need for viewport
#include "../platform.hpp"     // Needed for DIR_CUR, DIR_SEP, OpenGL/GLES
#include "../assert.hpp"       // Needed for assertions
#include "../warn.hpp"

#define ISPWR2(n) !(n & (n-1))

iRect Texture::getArea()
{
    return area;
}

int Texture::load(const char* filepath)
{
    // Local variables for extracting properties about the image
    GLuint n_colours = 0;
    GLenum format = (GLenum) NULL;

    // Load the image using SDL_image
	SDL_Surface* surface = IMG_Load(filepath);
	ASSERT_SDL(surface, "Opening image file");

    // Make sure the image length and width are powers of 2
    WARN_IF(!ISPWR2(surface->w), "Checking image width", "Not a 2^n");
    WARN_IF(!ISPWR2(surface->h), "Checking image width", "Not a 2^n");

    // If so, save the size of the surface for later use
    area = iRect(0, 0, surface->w, surface->h);

	//get number of channels in the SDL surface
    n_colours = surface->format->BytesPerPixel;
    switch(n_colours)
    {
        case 1: format = GL_LUMINANCE;          break;
        case 2: format = GL_LUMINANCE_ALPHA;    break;
        case 3: format = GL_RGB;                break;
        case 4: format = GL_RGBA;               break;
        default:
            LOG_E("Load texture failed","Image must be LUMINANCE, RGB or RGBA");
            return EXIT_FAILURE;
            break;
    }

    // Request an OpenGL unassigned GLuint to identify this texture
    glGenTextures(1, &handle);

    // Bind the texture object to the current block
    glBindTexture(GL_TEXTURE_2D, handle);

    // Set the texture’s properties
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Finally: convert the image to a texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, area.w, area.h, 0,
                    format, GL_UNSIGNED_BYTE, surface->pixels);

    // The original bitmap is no longer needed: delete it!
	SDL_FreeSurface(surface);

	// Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);


	// The return result reports the success of the operation
    return EXIT_SUCCESS;
}

int Texture::unload()
{
    // Free the texture from video memory
    glDeleteTextures(1, &handle);

    // Success !
    return EXIT_SUCCESS;
}

void Texture::draw(const fRect* src_ptr, const fRect* dst_ptr, float angle)
{
    // Crop the source rectangle if necessary
    fRect src(area);
    if(src_ptr)
        src = src_ptr->getInter(area);

    // Crop the destination rectangle if necessary
    fRect dst(global::viewport);
    if(dst_ptr)
        dst = (*dst_ptr);
        //dst = dst_ptr->getInter(global::viewport); // reacts badly with rotations

    // Set up position, rotation, colour
    glTranslatef(dst.x + dst.w/2, dst.y + dst.h/2, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    //glColor4f(255.0, 255.0, 255.0, 255.0); // reacts badly with Android

    // Bind the texture to which subsequent calls refer to
    glBindTexture(GL_TEXTURE_2D, handle);

    // Tell graphics hardware what to expect
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Set up the polygon in which we'll draw
    GLfloat
    min_x = -dst.w/2,
    min_y = -dst.h/2,
    max_x = -min_x,
    max_y = -min_y;
    GLfloat polygon[8]  =   {min_x, min_y,      // Top-left
                            max_x,  min_y,      // Top-right
                            min_x,  max_y,      // Bottom-left
                            max_x,  max_y };    // Bottom-right
    glVertexPointer(2, GL_FLOAT, 0, polygon);

    // Set up the binding of the skin (texture) to this polygon
    min_x = src.x/area.w;
    min_y = src.y/area.h;
    max_x = (src.x + src.w)/area.w;
    max_y = (src.y + src.h)/area.h;
   GLfloat skin[8]     =    {min_x, min_y,      // Top-left
                            max_x,  min_y,      // Top-right
                            min_x,  max_y,      // Bottom-left
                            max_x,  max_y };    // Bottom-right
    glTexCoordPointer(2, GL_FLOAT, 0, skin);

    // Draw everything (finally)!
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Stop drawing texture
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    // Reset back to normal
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, 0);
}
