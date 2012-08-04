#ifndef TINYXML_DUMP_H_INCLUDED
#define TINYXML_DUMP_H_INCLUDED

#include "tinyxml.h"

void dump_to_stdout(const char* pFilename);
void dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 );
#endif // TINYXML_DUMP_H_INCLUDED
