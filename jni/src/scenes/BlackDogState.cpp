#include "BlackDogState.hpp"

#include "../resources/GraphicsManager.hpp"

#include "../gameplay/things/AngelThing.hpp"
#include "../gameplay/things/DogThing.hpp"
#include "../gameplay/things/PixieThing.hpp"
#include "../global.hpp"                          // for viewport

/// CREATION, DESTRUCTION

BlackDogState::BlackDogState() :
GameState(),
parallax(),
obstacle(),
player_progress(STARTING_PROGRESS)
{
  // add the player character
  addThing(new AngelThing(V2i(player_progress, WINDOW_DEFAULT_H/2)));
  // add the dog
  addThing(new DogThing(V2i(0, WINDOW_DEFAULT_H/2)));
  // add the progress-mesure pixie
  addThing(new PixieThing(V2i()));
}

/// OVERRIDES GAMESTATE

int BlackDogState::update()
{
  int result;

  // Update dynamic game objects
  result = GameState::update();
  if(result != CONTINUE)
    return result;

  // Update difficulty based on player progress
  player_progress = ((AngelThing*)getHero())->getFurthestX();
  if(player_progress > PROGRESS_THRESHOLD)
    obstacle.setDifficulty(player_progress / (WINDOW_DEFAULT_W * 0.8f));

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

}
