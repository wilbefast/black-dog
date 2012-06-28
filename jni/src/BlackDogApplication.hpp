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
#ifndef BLACKDOGAPPLICATION_HPP_INCLUDED
#define BLACKDOGAPPLICATION_HPP_INCLUDED

#include "Application.hpp"

class BlackDogApplication : public Application
{
  /// METHODS
public:
  BlackDogApplication();
  /// OVERRIDES
protected:
  int loadResources();  // Load games resources into memory
};

#endif // BLACKDOGAPPLICATION_HPP_INCLUDED
