#pragma once

#include "Bank.h"
#include "Board.h"
#include "Config.h"
#include "Player.h"
#include <random>

/*!
 *  \addtogroup Dogan
 *  @{
 */

//! Public interfaces in the %Dogan library
namespace Dogan {
/**
 * @brief Interface for the Game class
 *
 * This class is the main class for playing
 */
class Game {
public:
  /**
   * @brief Construct a new Game object
   *
   * @param config A config object needed to set up the game.
   */
  Game(Config config = Config());

  /**
   * @brief Add a player to the game
   *
   * @param pid The player ID of the player to add
   */
  void addPlayer(int pid);

  /**
   * @brief Remove a player to the game
   *
   * @param pid The player ID of the player to remove
   */
  void removePlayer(int pid);

  /**
   * @brief
   *
   * @param playerID The player id of the player to give resources to
   * @param resources An array of integers representing the resources to give
   */
  void giveResources(int playerID, std::array<int, 5> resources);

  /**
   * @brief Roll two dice. Does not distribute resources
   *
   * @return int The result of the dice roll
   */
  int rollDice(void);

  /**
   * @brief Distribute all resources to players based on the dice roll
   *
   * @param numberRolled
   */
  void distributeResources(int numberRolled);

  /**
   * @brief Build a structure on the game board.
   * You only need to provide one representation of the location to build the
   * structure. The function will automatically determine the other
   * representations and will populate.
   *
   * @param playerID The player ID of the player building the structure
   * @param structType The Structure Type to build
   * @param tileLocation A Coordinate2D object representing a tile to build the
   * structure
   * @param direction The direction to build the structure
   * @param cost A cost array representing the cost of the structure. Should be
   * positive integers
   * @param mustBeAdjacent Whether the structure must be connected to a road
   */
  void buildStructure(int playerID, StructureType structType,
                      Coordinate2D tileLocation, Direction direction,
                      std::array<int, 5> cost, bool mustBeAdjacent = true);
  /**
   * @brief Purchase a development card
   *
   * @param playerID The player ID of the player purchasing the development card
   * @param cost The cost of the development card. Should be positive integers
   */
  void purchaseDevelopmentCard(int playerID, std::array<int, 5> cost);
  /**
   * @brief Trade resources between two players
   *
   * @param playerID1 The player ID of the first player
   * @param resources1 The resources the first player is trading to the second.
   * If negative, indicates the player is receiving resources
   * @param playerID2 The player ID of the second player
   * @param resources2 The resources the second player is trading to the first.
   * If negative, indicates the player is receiving resources
   */
  void tradeResources(int playerID1, std::array<int, 5> resources1,
                      int playerID2, std::array<int, 5> resources2);

  /**
   * @brief Use a robber to steal resources from a player
   *
   * @param playerID The player ID of the player using the robber
   * @param tileLocation A Coordinate2D object representing the tile to place
   * the robber
   * @param direction The direction of the structure to steal from. If the tile
   * has no structures, use Direction::NONE
   */
  void useRobber(int playerID, Coordinate2D tileLocation, Direction direction);

  /**
   * @brief Use the monopoly development card.
   * The monopoly development card allows the player to take all of a certain
   * resource from all other players
   *
   * @param playerID The player ID of the player using the monopoly card
   * @param resource The ResourceType to take
   */
  void useMonopolyDevelopmentCard(int playerID, ResourceType resource);
  /**
   * @brief Use the soldier development card.
   * The soldier development card allows the player to move the robber and steal
   * a resource from a player. It also increases the soldier count, and if the
   * player has either 5 soldiers played or the most soldiers played (the higher
   * of the two), they get an additional 2 victory points
   *
   * @param playerID The player ID of the player using the soldier card
   * @param tileLocation The tile location to move the robber to
   * @param direction The direction to steal from. If the tile has no
   * structures, use Direction::NONE
   */
  void useSoldierDevelopmentCard(int playerID, Coordinate2D tileLocation,
                                 Direction direction);
  /**
   * @brief Use the road development card.
   * The road development card allows the player to build up to two roads
   *
   * @param playerID The player ID of the player using the road card
   * @param tileLocations An array of two Coordinate2D objects representing the
   * tiles to build the roads on
   * @param directions An array of two Direction enums representing the
   * directions to build the roads
   */
  void useRoadDevelopmentCard(int playerID,
                              std::array<Coordinate2D, 2> tileLocations,
                              std::array<Direction, 2> directions);
  /**
   * @brief Use the take two development card.
   * Allows the player to take any two resources from the bank
   *
   * @param playerID The player ID of the player using the take two card
   * @param resources An array of the two resources to take
   */
  void useTakeTwoDevelopmentCard(int playerID,
                                 std::array<ResourceType, 2> resources);

  /**
   * @brief Gets an array representation of all the resource cards a player has.
   *
   * @param playerID The player ID of the player to get the count from. If -1,
   * get the bank resource count
   * @return const std::array<int, 5> An array of integers representing the
   * resources of the player/bank
   */
  const std::array<int, 5> getResourceCount(int playerID) const;
  /**
   * @brief Gets an array representation of all the development cards a player
   * has
   *
   * @param playerID The player ID of the player to get the count from. If -1,
   * get the bank development count
   * @return const std::array<int, 5> An array of integers representing the
   * development cards of the player/bank
   */
  const std::array<int, 5> getDevelopmentCount(int playerID) const;
  /**
   * @brief Get the amount of victory points a player has
   *
   * @param playerID The player ID of the player to get the count from
   * @return int The amount of victory points
   */
  int getVictoryPoints(int playerID) const;
  /**
   * @brief Checks if a structure exists on a tile
   *
   * @param coord The Coordinate2D object representing the tile
   * @param direction The direction of the structure
   * @param structureType The type of structure to check for
   * @return true
   * @return false
   */
  bool hasStructure(Coordinate2D coord, Direction direction,
                    StructureType structureType) const;

  friend std::ostream &operator<<(std::ostream &os, Game const &dg);

private:
  Config config; //!< The configuration object for the game
  std::uniform_int_distribution<pip>
      die;                       //!< A random number generator for dice rolls
  Bank bank;                     //!< The bank object for the game
  Board board;                   //!< The board object for the game
  std::map<int, Player> players; //!< The players of the game
  std::pair<int, int>
      mostSoldiers; //!< The player with the most soldiers played and how many
                    //!< soldiers they've played
  std::pair<int, int> longestRoad; //!< The player with the longest road and how
                                   //!< many roads they have
  std::mt19937 rengine;

  void stealResource(int playerID, int stolenPlayerID);
  void checkPlayerExists(int playerID) const;
  void checkPlayerCanAfford(int playerID, std::array<int, 5> cost) const;
  void checkBankCanAfford(ResourceType resourceType, int num) const;
  void checkPlayerHasDevelopmentCard(int playerID,
                                     DevelopmentType devType) const;
  void checkCoordinateValid(Coordinate2D coord) const;
  void checkResourceType(ResourceType resourceType) const;
};
} // namespace Dogan