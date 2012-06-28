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
#ifndef THING_HPP_INCLUDED
#define THING_HPP_INCLUDED

#include "../../resources/numerise.hpp"
#include "../../math/V2.hpp"
#include "../../graphics/Texture.hpp"

#include <list>

class Thing;

typedef std::list<Thing*> ThingList;
typedef ThingList::iterator ThingIter;

#include "../../scenes/GameState.hpp"  // for update
#include "events/ThingEvent.hpp"

class ColliderElement;

class Thing
{
    /// ATTRIBUTES
private:
  // hashed name of the type of this Thing
  str_id type;
  // does this Thing need to be cleaned up at the end of its update?
  bool dead;
protected:
  // main attributes
  V2f position;
  ColliderElement* body;
  // asynchronous messages
  EventList events;

  /// METHODS
public:
  // constructors, destructors
  Thing(V2f init_position, const char* type_name);
  Thing(V2f init_position, str_id init_type);
  Thing(Thing const& source);
  virtual ~Thing();
  // main methods
  void addEvent(ThingEvent* new_event);
  void deleteEvents();
  const EventList* getEvents();
  // accessors
  bool isDead() const;
  str_id getType() const;
  V2f getPosition() const;
  void move(V2f translation);
  void moveTo(V2f new_position);
  bool isColliding(Thing* other, V2i* side = NULL);
  bool isOutside(fRect* bounds, V2i* side = NULL);
  bool isLeaving(fRect* bounds, V2i* side = NULL);
  // overridden
  virtual void die();
  virtual void draw();
  virtual int update(GameState*, float delta);

  /// SUBROUTINES
protected:
    void consumeEvent(EventIter* i);
};

#endif // THING_HPP_INCLUDED
