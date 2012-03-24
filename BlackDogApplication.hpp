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
