#ifndef RESOURCEMANAGER_HPP_INCLUDED
#define RESOURCEMANAGER_HPP_INCLUDED

class ResourceManager;

#include "gameplay/things/Thing.hpp"

class ResourceManager
{
    /// ATTRIBUTES
    private:

    /// METHODS
    public:
    // constructors, destructors
    ResourceManager();
    ~ResourceManager();
    // memorise and forget
    int load();
    int unload();
    // instantiation of ideals
    Thing* instantiate(const char* name, V2f position);
    Thing* instantiate(str_id type, V2f position);

};

#endif // RESOURCEMANAGER_HPP_INCLUDED
