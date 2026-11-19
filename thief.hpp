//
// ФАЙЛ thief.hpp
//
#pragma once

#include "base_hero.hpp"
#include "i_spell_caster.hpp"

namespace game
{

// final: от вора никто не наследуется, продолжать иерархию незачем
class Thief final : public BaseHero, public ISpellCaster
{
public:
    Thief();
    Thief(std::string_view name, int gold);
    Thief(const Thief&)                = default;
    Thief(Thief&&) noexcept            = default;
    Thief& operator=(const Thief&)     = default;
    Thief& operator=(Thief&&) noexcept = default;
    ~Thief() noexcept override;

    [[nodiscard]] std::string_view GetKind() const { return "вор"; }

    [[nodiscard]] std::string_view GetClassName() const override { return "Вор"; }
    [[nodiscard]] int GetAttackDamage() const override;
    [[nodiscard]] std::unique_ptr<BaseHero> Clone() const override;

    // У вора нет бонуса к заклинаниям: его сила в удаче
    int CastSpell(SpellElement element) override;

private:
    // Вор не получает прибавок к урону
    static constexpr int BASE_DAMAGE         = 12;
    static constexpr int SPELL_BONUS_PERCENT = 0;
};

} // namespace game
