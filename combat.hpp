//
// ФАЙЛ combat.hpp
//
#pragma once

#include "i_combatant.hpp"
#include "spell.hpp"

namespace game
{

// Работает только с контрактом: не знает, герой перед ним или монстр
void Attack(ICombatant& attacker, ICombatant& target);

// Колдовать может только тот, кто реализует ISpellCaster
void CastSpellAt(ICombatant& who, ICombatant& target, SpellElement element);

} // namespace game
