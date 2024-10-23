#pragma once

#include <exception>
#include <string>

namespace Dogan {
/**
 * @brief Thrown when a player, or the bank does not have enough resources to perform an action
 * 
 */
class InsufficientResourcesException : std::exception {
public:
  InsufficientResourcesException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};
/**
 * @brief Thrown when a player, or the bank does not have enough development cards to perform an action
 * 
 */
class InsufficientDevelopmentsException : std::exception {
public:
  InsufficientDevelopmentsException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

/**
 * @brief Thrown when a player does not have enough available structures to build a structure
 * 
 */
class InsufficientStructuresException : std::exception {
public:
  InsufficientStructuresException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

/**
 * @brief Thrown when the same player is added to the game twice
 * 
 */
class SamePlayerException : std::exception {
public:
  SamePlayerException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

/**
 * @brief Thrown when the player attempts to access a building on a vertex that does not exist
 * 
 */
class NoSuchStructureException : std::exception {
public:
  NoSuchStructureException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

/**
 * @brief Thrown when the player attempts to access a type that does not exist
 * 
 */
class InvalidTypeException : std::exception {
public:
  InvalidTypeException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

/**
 * @brief Thrown when the player attempts to access a coordinate that does not exist
 * 
 */
class CoordinateNotFoundException : std::exception {
public:
  CoordinateNotFoundException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

/**
 * @brief Thrown when the player attempts to build a structure on a location that is invalid
 * 
 */
class BuildStructureException : std::exception {
public:
  BuildStructureException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

/**
 * @brief Thrown when the game tries to perform an action with a player that does not exist
 * 
 */
class PlayerNotFoundException : std::exception {
public:
  PlayerNotFoundException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

} // namespace Dogan