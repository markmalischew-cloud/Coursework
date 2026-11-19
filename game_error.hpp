//
// ФАЙЛ game_error.hpp
//
#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

namespace game
{

// Нарушение правила игры во время работы программы.
// Что с ним делать, решает вызывающий код
class GameError : public std::runtime_error
{
public:
    explicit GameError(const std::string& message)
        : std::runtime_error{ message }
    {}
};

// Правило 5: заклинание доступно, только если хватает маны
class NotEnoughManaError : public GameError
{
public:
    NotEnoughManaError(int required, int available)
        : GameError{ "не хватает маны: нужно " + std::to_string(required)
                     + ", есть " + std::to_string(available) }
    {}
};

class NotEnoughGoldError : public GameError
{
public:
    NotEnoughGoldError(int required, int available)
        : GameError{ "не хватает золота: нужно " + std::to_string(required)
                     + ", есть " + std::to_string(available) }
    {}
};

class InventoryFullError : public GameError
{
public:
    explicit InventoryFullError(std::size_t capacity)
        : GameError{ "инвентарь полон, слотов: " + std::to_string(capacity) }
    {}
};

// Правило 3: во время боя нельзя менять экипировку
class ForbiddenInCombatError : public GameError
{
public:
    explicit ForbiddenInCombatError(std::string_view action)
        : GameError{ "во время боя нельзя: " + std::string(action) }
    {}
};

} // namespace game
