#pragma once

#include <stdexcept>

class GameError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class FontError : public GameError {
public:
    explicit FontError(const std::string& err) : GameError(err){}
};

class TextureError : public GameError {
public:
    explicit TextureError(const std::string& err) : GameError(err){}
};

class CastError : public GameError {
public:
    explicit CastError(const std::string& err) : GameError(err){}
};