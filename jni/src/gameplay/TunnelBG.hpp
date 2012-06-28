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
#ifndef TUNNELBG_INCLUDED
#define TUNNELBG_INCLUDED

#include "Tunnel.hpp"
#include "../graphics/draw.hpp"

// background tunnel: purely decorative.

class TunnelBG : public Tunnel
{
  /// CONSTANTS
private:
  static draw::Colour COLOUR_FILL;
  static const int DEFAULT_SPEED = 1;
  /// METHODS
public:
  TunnelBG();
  /// OVERRIDES
public:
  void draw();
private:
  void new_height(unsigned int i);
};

#endif // TUNNELBG_INCLUDED
