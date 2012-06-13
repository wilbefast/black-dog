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

    cout << "anim: strip="<<strip<<", numFrames="<<numFrames<<endl;
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
