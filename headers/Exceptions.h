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

GameError::GameError(const std::string& err) : std::logic_error(err) {}
FontError::FontError(const std::string& err) : GameError(err) {}
TextureError::TextureError(const std::string& err) : GameError(err) {}
CastError::CastError(const std::string& err) : GameError(err) {}