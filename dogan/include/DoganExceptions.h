#pragma once

#include <exception>
#include <string>

class InsufficientResourcesException : std::exception {
    public:
        InsufficientResourcesException(std::string m) : message(m) {};
        const char *what() const noexcept override {
            return message.c_str();
        }
    private:
        std::string message;
};