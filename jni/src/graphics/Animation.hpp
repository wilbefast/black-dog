#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include "Graphic.hpp"

class Animation : public Graphic
{
    /// ATTRIBUTES
    private:
    iRect strip; // the whole area occupied by the animation
    int numFrames;

    /// METHODS
    public:
    // constructors, destructors
    Animation();
    // main methods
    void init(Texture* init_texture, iRect init_frame, int number_frames = 1);
    // accessors
    iRect getFrame(float subimage = 0) const;   // masks Graphic::getFrame()
    int getNumFrames() const;

};

#endif // ANIMATION_HPP_INCLUDED
