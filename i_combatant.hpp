//
// ФАЙЛ i_combatant.hpp
//
#pragma once

#include <string_view>

namespace game
{

// Контракт: тот, кто может участвовать в бою (герой или монстр)
class ICombatant
{
public:
    virtual ~ICombatant() = default;

    [[nodiscard]] virtual std::string_view GetName() const = 0;
    [[nodiscard]] virtual int GetAttackDamage() const = 0;
    virtual void TakeDamage(int damage) = 0;
    [[nodiscard]] virtual bool IsAlive() const = 0;
};

} // namespace game
