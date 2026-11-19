//
// ФАЙЛ monster.hpp
//
#pragma once

#include "i_combatant.hpp"
#include "i_monster_tactic.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace game
{

class Monster : public ICombatant
{
public:
    Monster(std::string_view name, int health, int attackDamage,
            std::unique_ptr<IMonsterTactic> tactic);
    Monster(const Monster&)            = delete;
    Monster(Monster&&)                 = delete;
    Monster& operator=(const Monster&) = delete;
    Monster& operator=(Monster&&)      = delete;
    ~Monster() noexcept override;

    // Контракт ICombatant
    [[nodiscard]] std::string_view GetName() const override { return m_name; }
    [[nodiscard]] int GetAttackDamage() const override { return m_attackDamage; }
    void TakeDamage(int damage) override;
    [[nodiscard]] bool IsAlive() const override { return m_health > 0; }

    // Динамическое конфигурирование: тактику можно заменить во время работы
    void SetTactic(std::unique_ptr<IMonsterTactic> tactic);

    // Решение принимает объект поведения, а не сам монстр
    [[nodiscard]] MonsterAction ChooseAction() const;

    [[nodiscard]] std::string_view GetTacticName() const;
    [[nodiscard]] int GetHealth() const { return m_health; }
    [[nodiscard]] int GetHealthPercent() const { return m_health * 100 / m_maxHealth; }

private:
    std::string                     m_name;
    int                             m_health;
    int                             m_maxHealth;
    int                             m_attackDamage;
    std::unique_ptr<IMonsterTactic> m_tactic;
};

} // namespace game
