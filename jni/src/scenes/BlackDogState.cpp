#include "BlackDogState.hpp"

#include "../resources/GraphicsManager.hpp"

#include "../gameplay/things/AngelThing.hpp"
#include "../gameplay/things/DogThing.hpp"
#include "../global.hpp"                          // for viewport

/// CREATION, DESTRUCTION

BlackDogState::BlackDogState() :
GameState(),
parallax(),
obstacle()
{
  // add the player character
  addThing(new AngelThing(V2i(WINDOW_DEFAULT_W/4, WINDOW_DEFAULT_H/2)));
  // add the dog
  addThing(new DogThing(V2i(0, WINDOW_DEFAULT_H/2)));
}

/// OVERRIDES GAMESTATE

int BlackDogState::update()
{
  int result;

  // Update dynamic game objects
  result = GameState::update();
  if(result != CONTINUE)
    return result;

  // Update background parallax tunnel
  parallax.update();

  // Update forground obstacle tunnel
  obstacle.update();

  // All clear
  return EXIT_SUCCESS;
}

void BlackDogState::draw()
{
  // Draw the background colour
  draw::rectangle(global::viewport, draw::Colour(36, 6, 15));

  // Draw the background parallax tunnel
  parallax.draw();

  // Draw the foreground obstacle tunnel
  obstacle.draw();

  // Draw dynamic game objects
  GameState::draw();

  // Draw user interface
  draw_progress_ui();
  draw_feather_ui();
}

/// QUERY

const TunnelFG* BlackDogState::getObstacle() const
{
  return &obstacle;
}

/// SUBROUTINES

void BlackDogState::draw_feather_ui()
{
  // constants
  static const int SIZE = 32, SPACING = -6;
  static Animation* feather_ui
    = GraphicsManager::getInstance()->get_animation("feather_ui");

  // cache
  fRect src, dest = fRect(-SPACING, -SPACING, SIZE, SIZE);
  int n_feathers = ((AngelThing*)getHero())->countFeathers();

  // iterate through each feather of total possible storage
  for(int i = 0; i < AngelThing::MAX_FEATHERS; i++, dest.x += SIZE+SPACING)
  {
    // frame 0 is a full feather, 1 is an empty one
    src = feather_ui->getFrame(i < n_feathers ? 0 : 1);
    feather_ui->getTexture()->draw(&src, &dest);
  }
}

void BlackDogState::draw_progress_ui()
{
  // constants
  static const int SIZE = 32, LEAD = 32;
  static Animation* pixie
    = GraphicsManager::getInstance()->get_animation("feather_ui");

  // cache
  float desired_x = ((AngelThing*)getHero())->getFurthestX() + LEAD;
  V2f desired(desired_x, obstacle.x_to_middle(desired_x));

  // static variables remain between executions of the function
  static float current_y = desired.y;

  /// Note to self: create "animation canvas" class as in HTML 5 version.
  /// The "AnimationElement" does this already but must be attached to a Thing.




    fRect dest(desired.x, current_y, 32, 32), src = pixie->getFrame(0);
    pixie->getTexture()->draw(&src, &dest);

  // move gradually towards the desired position, not all at once
  current_y = (9*current_y + 1*desired.y) / 10.0f;
}
