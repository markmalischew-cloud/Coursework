//
// ФАЙЛ thief.hpp
//
#pragma once

#include "base_hero.hpp"

namespace game
{

// final: от вора никто не наследуется, продолжать иерархию незачем
class Thief final : public BaseHero
{
public:
    Thief();
    Thief(std::string_view name, int gold);
    Thief(const Thief&)                = default;
    Thief(Thief&&) noexcept            = default;
    Thief& operator=(const Thief&)     = default;
    Thief& operator=(Thief&&) noexcept = default;
    ~Thief() override;

    [[nodiscard]] std::string_view GetClassName() const override { return "Вор"; }
    [[nodiscard]] int GetAttackDamage() const override;
    [[nodiscard]] std::unique_ptr<BaseHero> Clone() const override;

private:
    // Вор не получает прибавок к урону: его сила в удаче
    static constexpr int BASE_DAMAGE = 12;
};

} // namespace game
