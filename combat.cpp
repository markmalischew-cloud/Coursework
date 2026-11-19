//
// ФАЙЛ combat.cpp
//

#include "combat.hpp"

#include "i_spell_caster.hpp"

#include <iostream>
#include <stdexcept>

namespace game
{

void Attack(ICombatant& attacker, ICombatant& target)
{
    if (!attacker.IsAlive())
    {
        throw std::logic_error{ "мёртвый не может атаковать" };
    }

    const int damage = attacker.GetAttackDamage();
    std::cout << attacker.GetName() << " атакует " << target.GetName()
              << " (урон " << damage << ")\n";
    target.TakeDamage(damage);
}

void CastSpellAt(ICombatant& who, ICombatant& target, SpellElement element)
{
    // Проверка типа во время выполнения: умеет ли объект колдовать вообще
    if (auto* caster = dynamic_cast<ISpellCaster*>(&who))
    {
        const int damage = caster->CastSpell(element);
        target.TakeDamage(damage);
    }
    else
    {
        std::cout << who.GetName() << " не умеет колдовать\n";
    }
}

} // namespace game
