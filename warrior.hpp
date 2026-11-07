//
// ФАЙЛ warrior.hpp
//
#pragma once

#include "base_hero.hpp"

namespace game
{

class Warrior : public BaseHero
{
public:
    Warrior();
    Warrior(std::string_view name, int gold);
    Warrior(const Warrior&)                = default;
    Warrior(Warrior&&) noexcept            = default;
    Warrior& operator=(const Warrior&)     = default;
    Warrior& operator=(Warrior&&) noexcept = default;
    ~Warrior() override;

    [[nodiscard]] std::string_view GetClassName() const override { return "Воин"; }
    [[nodiscard]] int GetAttackDamage() const override;
    [[nodiscard]] std::unique_ptr<BaseHero> Clone() const override;

    // Дополняет описание базового класса
    [[nodiscard]] std::string Describe() const override;

private:
    static constexpr int BASE_DAMAGE          = 20;
    static constexpr int WEAPON_BONUS_PERCENT = 15;
};

} // namespace game
