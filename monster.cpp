//
// ФАЙЛ monster.cpp
//

#include "monster.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

namespace game
{

Monster::Monster(std::string_view name, int health, int attackDamage,
                 std::unique_ptr<IMonsterTactic> tactic)
    : m_name{ name }
    , m_health{ health }
    , m_maxHealth{ health }
    , m_attackDamage{ attackDamage }
    , m_tactic{ std::move(tactic) }
{
    if (m_name.empty())
    {
        throw std::invalid_argument{ "имя монстра не может быть пустым" };
    }

    if (m_health <= 0)
    {
        throw std::invalid_argument{ "здоровье монстра должно быть больше нуля" };
    }

    if (m_attackDamage < 0)
    {
        throw std::invalid_argument{ "урон монстра не может быть отрицательным" };
    }

    if (!m_tactic)
    {
        throw std::invalid_argument{ "у монстра должна быть тактика" };
    }

    std::cout << "[Монстр] Создан: " << m_name
              << " (тактика: " << m_tactic->GetName() << ")\n";
}

Monster::~Monster() noexcept
{
    std::cout << "[Монстр] Уничтожен: " << m_name << "\n";
}

void Monster::TakeDamage(int damage)
{
    if (damage < 0)
    {
        throw std::invalid_argument{ "урон не может быть отрицательным" };
    }

    m_health -= damage;
    if (m_health < 0)
    {
        m_health = 0;
    }

    std::cout << "[Монстр] " << m_name << " получил " << damage
              << " урона. Осталось здоровья: " << m_health << "\n";
}

void Monster::SetTactic(std::unique_ptr<IMonsterTactic> tactic)
{
    if (!tactic)
    {
        throw std::invalid_argument{ "у монстра должна быть тактика" };
    }

    m_tactic = std::move(tactic);
    std::cout << "[Монстр] " << m_name << " меняет тактику на: " << m_tactic->GetName() << "\n";
}

MonsterAction Monster::ChooseAction() const
{
    return m_tactic->Decide(GetHealthPercent());
}

std::string_view Monster::GetTacticName() const
{
    return m_tactic->GetName();
}

} // namespace game
