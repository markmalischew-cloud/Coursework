//
// ФАЙЛ mage.hpp
//
#pragma once

#include "base_hero.hpp"
#include "i_spell_caster.hpp"

namespace game
{

class Mage : public BaseHero, public ISpellCaster
{
public:
    Mage();
    Mage(std::string_view name, int gold);
    Mage(const Mage&)                = default;
    Mage(Mage&&) noexcept            = default;
    Mage& operator=(const Mage&)     = default;
    Mage& operator=(Mage&&) noexcept = default;
    ~Mage() noexcept override;

    [[nodiscard]] std::string_view GetKind() const { return "маг"; }

    [[nodiscard]] std::string_view GetClassName() const override { return "Маг"; }
    [[nodiscard]] int GetAttackDamage() const override;
    [[nodiscard]] std::unique_ptr<BaseHero> Clone() const override;

    // Полностью заменяет описание базового класса
    [[nodiscard]] std::string Describe() const override;

    // Классовый бонус мага ко всем заклинаниям
    int CastSpell(SpellElement element) override;

private:
    static constexpr int BASE_DAMAGE         = 8;
    static constexpr int SPELL_BONUS_PERCENT = 20;
};

} // namespace game
