#pragma once

#include <stdexcept>

class GameError : public std::logic_error {
public:
    explicit GameError(const std::string& err);
};

class FontError : public GameError {
public:
    explicit FontError(const std::string& err);
};

class TextureError : public GameError {
public:
    explicit TextureError(const std::string& err);
};

class CastError : public GameError {
public:
    explicit CastError(const std::string& err);
};