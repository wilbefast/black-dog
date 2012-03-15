#include "ResourceManager.hpp"

#include "numerise.hpp"
#include "warn.hpp"
#include "assert.hpp"
#include "file.hpp"
//#include "tinyxml/tinyxml.h"

/// CONSTRUCTORS, DESTRUCTORS
ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

/// LOAD/UNLOAD RESOURCES
int ResourceManager::load()
{
    // load game resources

    // All clear
    return EXIT_SUCCESS;
}

int ResourceManager::unload()
{
    // free game resources

    // All clear
    return EXIT_SUCCESS;
}

/// INSTANTIATION OF IDEALS
Thing* ResourceManager::instantiate(const char* name, V2f position)
{
    return instantiate(numerise(name), position);
}

Thing* ResourceManager::instantiate(str_id type, V2f position)
{
    Thing* result = NULL;

    WARN("ResourceManager::instantiate","couldn't find requested type");

    // Return the result (NULL if not found)
    return result;
}
