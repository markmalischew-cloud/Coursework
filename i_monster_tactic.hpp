//
// ФАЙЛ i_monster_tactic.hpp
//
#pragma once

#include <string_view>

namespace game
{

enum class MonsterAction
{
    eAttack,
    eFlee,
    eBegForMercy
};

[[nodiscard]] constexpr std::string_view ToString(MonsterAction action)
{
    switch (action)
    {
        case MonsterAction::eAttack:      return "атаковать";
        case MonsterAction::eFlee:        return "бежать";
        case MonsterAction::eBegForMercy: return "просить пощады";
    }
    return "неизвестно";
}

// Объект поведения: решает, что монстр делает в свой ход
class IMonsterTactic
{
public:
    virtual ~IMonsterTactic() = default;

    [[nodiscard]] virtual MonsterAction Decide(int healthPercent) const = 0;
    [[nodiscard]] virtual std::string_view GetName() const = 0;
};

} // namespace game
