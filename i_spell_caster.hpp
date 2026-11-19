//
// ФАЙЛ i_spell_caster.hpp
//
#pragma once

#include "spell.hpp"

namespace game
{

// Контракт: умеет колдовать заклинания стихий
class ISpellCaster
{
public:
    virtual ~ISpellCaster() = default;

    // Колдует заклинание и возвращает нанесённый урон.
    // Бросает NotEnoughManaError, если маны не хватает
    virtual int CastSpell(SpellElement element) = 0;
};

} // namespace game
