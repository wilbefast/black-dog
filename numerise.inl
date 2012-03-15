// Inline file: a special implementation that is included

using namespace std;

inline str_id numerise(const char* str)
{
    str_id hash = INIT_HASH;
    unsigned int i = 0;
    while(str[i])
    {
        hash = REHASH(str[i], hash);
        i++;
    }
    return hash;
}

