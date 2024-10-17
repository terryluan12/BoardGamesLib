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