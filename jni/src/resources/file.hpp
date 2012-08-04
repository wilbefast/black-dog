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
#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

#include <string>

#include "../platform.hpp"         // ASSET_PATH_PATH, BUFFER_XML
#include "tinyxml/tinyxml.h"


#define GET_ASSET(x) ASSET_PATH x

namespace io
{
    const int BLOCK_SIZE =  8;  /// FIXME different for windows
    const int MAX_BLOCKS =  1024;

    std::string path_to_name(const char* filepath);
    std::string name_to_path(const char* name, const char* extension = NULL);
    int read_text(const char* file_path, char** destination);
    int read_xml(const char* file_path, TiXmlDocument* destination);
}


#endif // FILE_HPP_INCLUDED
