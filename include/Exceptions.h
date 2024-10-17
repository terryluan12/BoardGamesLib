#pragma once

#include <exception>
#include <string>

class NoSuchDirection : std::exception {
public:
  NoSuchDirection(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};
