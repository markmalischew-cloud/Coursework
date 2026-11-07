//
// ФАЙЛ mage.hpp
//
#pragma once

#include "base_hero.hpp"

namespace game
{

class Mage : public BaseHero
{
public:
    Mage();
    Mage(std::string_view name, int gold);
    Mage(const Mage&)                = default;
    Mage(Mage&&) noexcept            = default;
    Mage& operator=(const Mage&)     = default;
    Mage& operator=(Mage&&) noexcept = default;
    ~Mage() override;

    [[nodiscard]] std::string_view GetClassName() const override { return "Маг"; }
    [[nodiscard]] int GetAttackDamage() const override;
    [[nodiscard]] std::unique_ptr<BaseHero> Clone() const override;

    // Полностью заменяет описание базового класса
    [[nodiscard]] std::string Describe() const override;

private:
    static constexpr int BASE_DAMAGE         = 8;
    static constexpr int SPELL_BONUS_PERCENT = 20;
};

} // namespace game
