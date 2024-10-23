#pragma once

#include <exception>
#include <string>

class NoSuchDirectionException : std::exception {
public:
  NoSuchDirectionException(std::string m) : message(m){};
  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};
