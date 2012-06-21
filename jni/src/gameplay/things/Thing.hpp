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
