#ifndef LIONHEART_GET_PLAYERS_CONFIGURED_HPP
#define LIONHEART_GET_PLAYERS_CONFIGURED_HPP


#include "Player/SittingDuck.hpp"
#include "Player/Goldfish.hpp"
#include "Player/ChargingBadger.hpp"
#include "Player/WildBoar.hpp"
#include "Player/SnappingTurtle.hpp"
#include "Player/CirclingShark.hpp"
#include "Player/CrouchingTiger.hpp"
#include "Player/HiddenDragon.hpp"
#include "Player/ExamplePlayer.hpp"
#include "Player/ChrisIrvine.hpp"
#include "Player/BrandonSmith.hpp"
#include "Player/MathewWarenski.hpp"

namespace lionheart
{
inline std::vector<std::shared_ptr<lionheart::Player>> getPlayers()
{
  std::vector<std::shared_ptr<lionheart::Player>> players;
  
  players.push_back(std::make_shared<lionheart::SittingDuck>());
  players.push_back(std::make_shared<lionheart::Goldfish>());
  players.push_back(std::make_shared<lionheart::ChargingBadger>());
  players.push_back(std::make_shared<lionheart::WildBoar>());
  players.push_back(std::make_shared<lionheart::SnappingTurtle>());
  players.push_back(std::make_shared<lionheart::CirclingShark>());
  players.push_back(std::make_shared<lionheart::CrouchingTiger>());
  players.push_back(std::make_shared<lionheart::HiddenDragon>());
  players.push_back(std::make_shared<lionheart::ExamplePlayer>());
  players.push_back(std::make_shared<lionheart::ChrisIrvine>());
  players.push_back(std::make_shared<lionheart::BrandonSmith>());
  players.push_back(std::make_shared<lionheart::MathewWarenski>());
  return players;
}
}
#endif

