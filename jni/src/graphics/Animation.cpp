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
#include "Animation.hpp"

using namespace std;

// Constructors, destructors
Animation::Animation() :
Graphic()
{
}

// Main methods
void Animation::init(Texture* init_texture, iRect init_frame, int number_frames)
{
    // standard initialisations
    Graphic::init(init_texture, init_frame);

    // partition strip into frames
    strip = iRect(frame.x, frame.y, frame.w*number_frames, frame.h);
    numFrames = floor((double)strip.w/frame.w);
}

// Accessors

int Animation::getNumFrames() const
{
    return numFrames;
}

iRect Animation::getFrame(float subimage) const
{
    // masks the parent's accessor if a subimage is specified
    if(!subimage)
        return Graphic::getFrame();

    // offset the appropriate number of frames
    V2i offset(floor(subimage)*frame.w, 0);
    if(offset > strip.getSize())
        // out of bounds
        return frame;
    else
        // return the appropriate subsection
        return (frame + offset);
}
