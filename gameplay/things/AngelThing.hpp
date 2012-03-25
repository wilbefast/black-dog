#ifndef ANGELTHING_HPP_INCLUDED
#define ANGELTHING_HPP_INCLUDED

#include "Thing.hpp"

// attributes
#include "../../graphics/Animation.hpp"
#include "elements/AnimatedElement.hpp"
#include "elements/MovementElement.hpp"
#include "elements/ResourceElement.hpp"

class AngelThing : public Thing
{
  /// NESTING
public:
  class State
  {
  private:
    static unsigned int next_id;
  public:
    const float gravity, max_speed;
    const unsigned int id;
    State(float _gravity, float _max_speed);
    bool operator==(const State& other) const;
  };

  /// CONSTANTS
private:
  // true constants
  static const float DEFAULT_THRUST = 6.0f;
  static const float FRICTION = 0.2f;
  static const int INIT_FEATHERS = 8;
  static const int FEATHER_INTERVAL = 45;
  static const int STUN_DURATION = 20;
  static const int SPRITE_DEFAULT_W = 64;
  static const int SPRITE_DEFAULT_H = 64;
  // G++ won't compile if these are const: clearly I suck at programming :'(
  static State FLAPPING;
  static State GLIDING;
  static State FALLING;
  static State STUNNED;
  static State DEAD;
  // pseudo-constants: depend on the size of the screen so initialised
  static float THRUST;
  static float DANGER_THRESHOLD;
  static float DEATH_THRESHOLD;


  /// ATTRIBUTES
private:
  State& state;
  AnimatedElement graphic;
  //MovementElement movement;
  ResourceElement feathers;


  /// METHODS
public:
  // creation
  AngelThing(V2i _position);
  // overrides
  void draw();
  int update(GameState* context);
};

#endif // ANGELTHING_HPP_INCLUDED

/*

function Player(init_x, init_y)
{
    // ATTRIBUTES (PRIVATE)
    var body = new AnimationCanvas(Player.anim_body, Player.SIZE, 0.2),
	weights = new AnimationCanvas(Player.anim_weights, [64, 64], 0.2),
    	wings = [ new AnimationCanvas(Player.anim_wings[0], [64, 64], 0.1),
               		new AnimationCanvas(Player.anim_wings[1], [64, 64], 0.1) ],
        black_dog = new AnimationCanvas(Player.anim_black_dog, [80,128], 0.2);
    	// player character position
    	pos = [init_x , init_y ],
    	pos_prev = [pos[0], pos[1]],
    	// gameplay state of character
    	state = Player.EState.GLIDE,
    	rise = false,
    	// physical state
    	speed = [ 0.0, 0.0 ] ,
    	droppingFeather = 0,
    	feathers_left = Player.INIT_FEATHERS,
    	// feather recovery interval
    	feather_timer = Player.FEATHER_INTERVAL,
    	victory = false,
        stun_timer = -1,
        draw_weights = true;
    // needed for wings to line up: include offset in constructor maybe?
    weights.setOffset([0, Player.SIZE[1]/2]);

    /// METHODS (PUBLIC)

    this.drawWeights = function(b) { draw_weights = b; }

    this.setVictory = function()
    {
	play_snd("cloth.wav");
    	victory = true;
    	body = new AnimationCanvas(Player.anim_body_end, [64, 64], 0.2);
    }

    this.countFeathersLeft = function() { return feathers_left; }

    this.makeWeight = function()
    {
    	return new Weight([pos[0], pos[1]+Player.SIZE[1]/3 ]);
    }

    this.makeCloak = function()
    {
    	return new Cloak([pos[0], pos[1] ]);
    }

    this.makeFeather = function()
    {
    	if(feathers_left)
    	{
    		droppingFeather --;
    	 	feathers_left -= 1;
    	 	var x = pos[0]-16 + Math.random()*droppingFeather*32;
    	 	var y = pos[1]-16 + Math.random()*droppingFeather*16;

    		return new Feather([x, y]);
    	}
    	else
    		droppingFeather = 0;
    }

    // is the angel going up (true) or down (false)?
    this.setRise = function(new_rise) { rise = new_rise; }

    this.draw = function()
    {
        // draw body between wings
        wings[1].draw(pos);
        body.draw(pos);
	if(draw_weights)
	  weights.draw(pos);
        wings[0].draw(pos);

	// draw the black dog
        if(pos[0] < Player.DANGER_ZONE || black_dog.getSpeed() != 0.0)
		black_dog.draw([35, pos[1]]);
    }

    this.update = function(tunnel)
    {
        // un-stun after a certain duration
        if(stun_timer == 0)
        {
            setState(Player.EState.FALL);
            stun_timer = -1;

        }
        else if(stun_timer > 0)
            stun_timer -= 1;


    	// deal with input and physics
        control();
        move();

	// check for death
        if(pos[0] < Player.DEATH_ZONE)
	{
	    setState(Player.EState.DIE);
	    return Player.EUpdateRes.DEATH;
	}
        // otherwise deal with other stuff

	//animate both wings
        for(i=0; i<2; i++)
            wings[i].animate();
        body.animate();
	weights.animate();

	// animate the black dog!
	animateDog();

        // recover feathers over time
        regenerate();

        // check for collisions
	var coltop = isCollidingTop(tunnel),
	    colbot = isCollidingBottom(tunnel);
        if(!victory && (coltop || colbot))
        {
        	var delta = coltop ? -1 : 1;
		// snap out of contact
		var snap = 32;	// max snap amount
		while(isColliding(tunnel) && snap > 0)
		{
		  pos[0] -= 1;
		  pos[1] -= 2*delta;
		  snap--;
		}
		// bounce away
		speed[0] = -5;
		speed[1] = (delta < 0) ? 2 : -7;
		// set for stun (teehee)
		setState(Player.EState.STUN);

        }

        // if we need to drop a feather let the game know
        if(droppingFeather > 0)
        	return Player.EUpdateRes.FEATHER;

	// other return the standard return code
        return Player.EUpdateRes.CONTINUE;
    }

    /// METHODS (PRIVATE)

    function isCollidingBottom(tunnel)
    {
      return !tunnel.contains(pos[0], pos[1] + Player.SIZE[1]/8);
    }

    function isCollidingTop(tunnel)
    {
      return !tunnel.contains(pos[0], pos[1] - Player.SIZE[1]/8);

    }

    function isColliding(tunnel)
    {
      return (isCollidingTop(tunnel) || isCollidingBottom(tunnel));
    }

    function setState(new_state)
    {
      // undo all "stop next"s for animations
      for(i=0; i<2; i++)
	wings[i].stopNext(-1);


        switch(new_state.id)
        {
            case Player.EState.FALL.id:
		for(i=0; i<2; i++)
		{
		  if(wings[0].getSpeed() == 0.0)
		    wings[i].setSubimage(0.0);
		  else
		    wings[i].stopNext(0);
		}
                break;



            case Player.EState.FLAP.id:
		// boost upwards
		play_snd("flap.wav");
		speed[1] = -Player.THRUST;
		// reset feather regeneration timer
		feather_timer = Player.FEATHER_INTERVAL;

		// drop a feather unless victory has occured
		if(!victory)
		      droppingFeather++;
		// set animation
                for(i=0; i<2; i++)
                {
		    wings[i].setSubimage(0.0);
                    wings[i].setSpeed(0.2);
                }
                break;


            case Player.EState.GLIDE.id:
                for(i=0; i<2; i++)
                {
                    wings[i].setSpeed(0.0);
                    wings[i].setSubimage(6.0);
                }
                break;


            case Player.EState.STUN.id:
		stun_timer = Player.STUN_DURATION;
		feather_timer = Player.FEATHER_INTERVAL;
		for(i=0; i<2; i++)
		  {
		    wings[i].setSubimage(3.0);
		    wings[i].setSpeed(0.0);
		  }
		if(state.id != new_state.id)
		{
		  droppingFeather += Player.STUN_FEATHERS;
		  play_snd("scream.wav");
		}
		break;

	    case Player.EState.DIE.id:
	      draw_weights = false;
	      play_snd("swallow.wav");
	      black_dog.setSubimage(15);
	      pos[0] = 48;
	      for(i=0; i<2; i++)
	      {
		  wings[i].setSubimage(3.0);
		  wings[i].setSpeed(0.0);
	      }
	      break;

            default:
                break;
        }

        // overwrite the previous start at the very end!
        state = new_state;
    }

    function control()
    {
        switch(state.id)
        {
            case Player.EState.FALL.id:
		// try to rise up from fall
                if(rise)
                {
                    // check if feathers remain
                    if(feathers_left > 0)
                        // flap wings if possible
                        setState(Player.EState.FLAP);
                    else
			// otherwise assume glide
                        setState(Player.EState.GLIDE);
                }

            case Player.EState.GLIDE.id:
		// glide turns to fall if mouse is released
                if(!rise)
                    setState(Player.EState.FALL);


                break;

            case Player.EState.FLAP.id:
            	// if falling currently
                if(speed[1] > 0.0)
                {
		    // flap turn to glide if holding down click/touch
                    if(rise)
                        setState(Player.EState.GLIDE);
		    // if released it turns into a fall
                    else
                        setState(Player.EState.FALL);
                }
                // if rising currently and not trying to rise higher
                else if(!rise)
                    // dampened upward speed (smaller boosts for short clicks)
                    speed[1] += Player.FRICTION;
                break;

            default:
                break;

        }
    }


    function animateDog()
    {
	// local variables
        var breath_start = 11, breath_end = 14,
		sub = black_dog.getSubimage();

	// if not, check for danger: show dog if in the "dange'ah' zo'own'!"
	if(pos[0] < Player.DANGER_ZONE && !victory)
	{
	    // play spawn sound
	    if(pos_prev[0] >= Player.DANGER_ZONE)
	      play_snd("slime.wav");

	    // we want the dog to breath in and out when it arrives
	    if(sub <= breath_start+0.6)
		black_dog.setSpeed(0.2);

	    else if(sub >= breath_end+0.4)
	    {
		black_dog.setSpeed(-0.2);
		black_dog.stopNext(0);
	    }
	}

	// if not,hide the dog, as the danger has passed
	else
	{
	  if(!victory && pos_prev[0] < Player.DANGER_ZONE)
	      play_snd("slime.wav");

	  if (black_dog.getSpeed() > 0.0)
	  {
	      black_dog.setSpeed(-0.2);
	      black_dog.stopNext(0);
	  }
	}

	// finally: do your thing!
	black_dog.animate();
    }

    function move()
    {
      // save previous position
      for(i=0; i<2; i++) pos_prev[i] = pos[i];

        // accelerate to terminal velocity
        speed[1] += state.gravity;

        // technically horizontal speed is not actually used... for now
        if(speed[1] > state.max_speed)
            speed[1] = state.max_speed;
        // move forward normally
        if(!victory)
	{
		pos[1] += speed[1];
	    	pos[0] += speed[0];
	    	if(speed[0] < 0 || pos[0] > canvas.width/3)
	    		speed[0] = (Math.abs(speed[0]) > 0.1) ? speed[0]*0.9 : 0.0;
	    	else if(speed[0] == 0.0)
	    		speed[0] = (speed[0] < 0.9) ? speed[0]+0.1 : 1.0;
	}
	// fixed movement for end game
        else
        {
		// move away from dog
		if(pos[0] < canvas.width/4)
			pos[0] += 1;

		// move to center of screen vertically
        	var delta = pos[1] - canvas.height/2;
        	if(Math.abs(delta) < 8)
        		return;

        	var side = (delta > 0) ? -1 : 1;
        	pos[1] += side;




        }

    }


    function regenerate()
    {
    	// recover feathers
        if(feathers_left != Player.INIT_FEATHERS)
        {
	        if(feather_timer == 0)
	        {
	        	feather_timer = Player.FEATHER_INTERVAL;
	        	feathers_left++;
	        }
	        else
	        	feather_timer--;
        }
    }


}

*/
