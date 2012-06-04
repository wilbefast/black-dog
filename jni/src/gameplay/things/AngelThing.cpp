#include "AngelThing.hpp"

#include "../../global.hpp"
#include "../../resources/AudioManager.hpp"
#include "../../resources/GraphicsManager.hpp"
#include "elements/ColliderElement.hpp"
#include "../../scenes/BlackDogState.hpp"

/// CONSTANTS

const float AngelThing::THRUST = 6.0f;
const float AngelThing::FRICTION = 0.2f;

/// PLAYER STATES

unsigned int AngelThing::State::next_id = 0;

AngelThing::State::State(float _gravity, float _speed_max) :
gravity(_gravity),
speed_max(_speed_max),
id(State::next_id)
{
  AngelThing::State::next_id++;
}

bool AngelThing::State::operator==(const AngelThing::State& other) const
{
  return (id == other.id);
}


/// CONSTRUCTION & DESTRUCTION

#define STR_UNSTUN "unstun"
#define STR_REFEATHER "refeather"

#define FLAPPING_ID 0
#define GLIDING_ID 1
#define FALLING_ID 2
#define STUNNED_ID 3
#define DEAD_ID 4

AngelThing::AngelThing(V2i _position) :
Thing(_position, "angel"),
FLAPPING(0.2f, 0.2f),
GLIDING(0.1f, 0.7f),
FALLING(0.3f, 10.0f),
STUNNED(0.3f, 5.0f),
DEAD(1.0f, 0.0f),
state(&FALLING),
graphic(this, V2f(SPRITE_W, SPRITE_H)),
movement(this, THRUST),
feathers(this, INIT_FEATHERS),
stun_timer(this, STR_UNSTUN),
feather_timer(this, STR_REFEATHER, FEATHER_INTERVAL)
{
  // set initial sprite
  Animation* wraith = GraphicsManager::getInstance()->get_animation("wraith");
  graphic.setSprite(wraith, 0.1f);

  // angel is collideable
  body = new ColliderElement(this, V2d(V2d(HITBOX_W, HITBOX_H)));
}

/// OVERRIDES

void AngelThing::draw()
{
  // draw the sprite
  graphic.draw();
}

int AngelThing::update(GameState* context)
{
  // treat events
  for(EventIter i = events.begin(); i != events.end(); i++)
    treatEvent(*i);

  // treat input
  treatInput(context);

  // apply physics
  movement.addSpeed(V2f(0.0f, state->gravity));

  // move based on input and physics
  movement.update(context);
  if(movement.getSpeed().y > state->speed_max)
    movement.setSpeed(V2f(0.0f, state->speed_max));

  // decrement timers
  if(stun_timer.ticking())
    stun_timer.decrement();
  if(feather_timer.ticking())
    feather_timer.decrement();

  // check for death
  checkCollision(context);

  // animate the sprite
  graphic.update(context);

  // nothing interrupted execution, so continue looping
  return Thing::update(context);
}


/// SUBROUTINES

void AngelThing::setState(State& new_state)
{
  switch(new_state.id)
  {
    case FALLING_ID:
      /*
      if(wings[0].getSpeed() == 0.0)
		    wings[i].setSubimage(0.0);
		  else
		    wings[i].stopNext(0);
      */
    break;

    case FLAPPING_ID:
      AudioManager::getInstance()->play_sound("flap");
      movement.setSpeed(V2f(0.0f, -state->speed_max*THRUST));
      feather_timer.set(FEATHER_INTERVAL);
      /*
      // drop a feather unless victory has occured
      if(!victory)
		      droppingFeather++;
        // set animation
          wings[i].setSubimage(0.0);
          wings[i].setSpeed(0.2);
      */
    break;

    case GLIDING_ID:
    /*
      wings[i].setSpeed(0.0);
      wings[i].setSubimage(6.0);
    */
    break;

    case STUNNED_ID:
      stun_timer.set(STUN_DURATION);
      feather_timer.set(FEATHER_INTERVAL);
      /*
        wings[i].setSubimage(3.0);
        wings[i].setSpeed(0.0);
        if(state.id != new_state.id)
        {
          droppingFeather += Player.STUN_FEATHERS;
          play_snd("scream.wav");
        }
      */
    break;

    case DEAD_ID:
    /*
      draw_weights = false;
      play_snd("swallow.wav");
      black_dog.setSubimage(15);
      pos[0] = 48;
		  wings[i].setSubimage(3.0);
		  wings[i].setSpeed(0.0);
    */
    break;

    default:
    break;
  }

  // overwrite the previous start at the very end!
  state = &new_state;
}

int AngelThing::treatEvent(ThingEvent* event)
{
  // local variables
  static str_id UNSTUN = numerise(STR_UNSTUN),
                REFEATHER = numerise(STR_REFEATHER);

  // stun duration finished event
  if(event->getType() == UNSTUN)
    setState(FALLING);

  // feather regeration finished event
  else if (event->getType() == REFEATHER)
  {
    feathers.deposit();
    // remember to reset the timer
    feather_timer.set(FEATHER_INTERVAL);
  }

    // nothing to report
    return GameState::CONTINUE;
}

int AngelThing::treatInput(GameState* context)
{
  // get an input handle and read updates
  GameState::Input* input = context->getInput();

  // pressing this step
  if(input->clicking)
  {
      switch(state->id)
      {
        case FALLING_ID: /// FIXME -- ids change each time instance is created!!!!
          if(feathers.anyLeft())
            setState(FLAPPING);
          else
            setState(GLIDING);
        break;

        case FLAPPING_ID:
          // if moving downwards
          if(movement.getSpeed().y > 0.0f)
            setState(GLIDING);
        break;
      }
  }

  // not pressing this step
  else
  {
    // if moving upwards
    if(movement.getSpeed().y < 0.0f)
      // apply dampening: hold down longer to fly higher
      movement.addSpeed(V2f(0.0f, FRICTION));

    // if moving downwards
    else switch(state->id)
    {
      case GLIDING_ID:
      case FLAPPING_ID:
        setState(FALLING);
      break;
    }
  }

  // nothing to report
  return GameState::CONTINUE;
}

int AngelThing::checkCollision(GameState* context)
{
  const TunnelFG* obstactle = ((BlackDogState*)context)->getObstacle();
  fRect hitbox = body->getOffsetBox();


  int collision = obstactle->collidingRect(hitbox);
  if(collision)
  {
    // snap out of contact
    int snap = 32;	// max snap amount
    while(collision && snap > 0)
    {
      hitbox += V2f(1, 2*collision);
      snap--;
      collision = obstactle->collidingRect(hitbox);
    }
    // bounce away
    movement.setSpeed(V2f(-5.0f, (collision < 0) ? 2 : -7));
    // set for stun (teehee)
    setState(STUNNED);
  }

  // nothing to report
  return GameState::CONTINUE;
}
