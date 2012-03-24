#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

#include "../platform.hpp"         // ASSET_PATH_PATH, BUFFER_XML
//#include "tinyxml/tinyxml.h"


#define GET_ASSET(x) ASSET_PATH x

namespace io
{
    const int BLOCK_SIZE =  8;  /// FIXME different for windows
    const int MAX_BLOCKS =  1024;

    int read_text(const char* source_file, char** destination);
    //int read_xml(const char* source_file, TiXmlDocument* destination);
}


#endif // FILE_HPP_INCLUDED
