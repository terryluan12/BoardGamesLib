#pragma once

#include <exception>
#include <string>

class InsufficientFundsException : std::exception {
public:
  InsufficientFundsException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class InsufficientResourcesException : std::exception {
public:
  InsufficientResourcesException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class InsufficientDevelopmentsException : std::exception {
public:
  InsufficientDevelopmentsException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class InsufficientStructuresException : std::exception {
public:
  InsufficientStructuresException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class SamePlayerException : std::exception {
public:
  SamePlayerException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class NoSuchStructureException : std::exception {
public:
  NoSuchStructureException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class InvalidTypeException : std::exception {
public:
  InvalidTypeException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class CoordinateNotFoundException : std::exception {
public:
  CoordinateNotFoundException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class SameStructureException : std::exception {
public:
  SameStructureException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class PlayerNotFoundException : std::exception {
public:
  PlayerNotFoundException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class UndefinedBehaviourException : std::exception {
public:
  UndefinedBehaviourException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};

class NoVillageException : std::exception {
public:
  NoVillageException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};