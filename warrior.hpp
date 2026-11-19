//
// ФАЙЛ warrior.hpp
//
#pragma once

#include "base_hero.hpp"
#include "i_spell_caster.hpp"

namespace game
{

// Множественное наследование: абстрактный класс BaseHero и интерфейс ISpellCaster
class Warrior : public BaseHero, public ISpellCaster
{
public:
    Warrior();
    Warrior(std::string_view name, int gold);
    Warrior(const Warrior&)                = default;
    Warrior(Warrior&&) noexcept            = default;
    Warrior& operator=(const Warrior&)     = default;
    Warrior& operator=(Warrior&&) noexcept = default;
    ~Warrior() noexcept override;

    // Скрывает BaseHero::GetKind(): раннее связывание, не переопределение
    [[nodiscard]] std::string_view GetKind() const { return "воин"; }

    [[nodiscard]] std::string_view GetClassName() const override { return "Воин"; }
    [[nodiscard]] int GetAttackDamage() const override;
    [[nodiscard]] std::unique_ptr<BaseHero> Clone() const override;

    // Дополняет описание базового класса
    [[nodiscard]] std::string Describe() const override;

    // Контракт ISpellCaster: у воина нет бонуса к заклинаниям
    int CastSpell(SpellElement element) override;

private:
    static constexpr int BASE_DAMAGE          = 20;
    static constexpr int WEAPON_BONUS_PERCENT = 15;
    static constexpr int SPELL_BONUS_PERCENT  = 0;
};

} // namespace game
