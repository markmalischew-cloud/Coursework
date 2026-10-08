//
// ФАЙЛ hero.cpp
//

#include "hero.hpp"
#include <iostream>

namespace game
{

Hero::Hero(std::string_view name, int health, int mana, int gold)
    : m_name{ name }
    , m_health{ health }
    , m_mana{ mana }
    , m_gold{ gold }
{
    if (m_name.empty())
    {
        m_name = "Неизвестный Герой";
    }

    if (m_health <= 0)
    {
        m_health = 100;
    }

    if (m_mana < 0)
    {
        m_mana = 0;
    }

    if (m_gold < 0)
    {
        m_gold = 0;
    }
}

Hero::~Hero()
{
    std::cout << "[Герой] " << m_name << " уничтожен\n";
}

void Hero::TakeDamage(int damage)
{
    if (damage < 0)
    {
        return;
    }

    m_health -= damage;
    if (m_health < 0)
    {
        m_health = 0;
    }

    std::cout << "[Герой] " << m_name << " получил " << damage 
              << " урона. Осталось здоровья: " << m_health << "\n";
}

bool Hero::UseMana(int amount)
{
    if (amount <= 0)
    {
        return false;
    }

    if (m_mana < amount)
    {
        std::cout << "[Герой] " << m_name << ": Недостаточно маны! (Нужно: " 
                  << amount << ", Есть: " << m_mana << ")\n";
        return false;
    }

    m_mana -= amount;
    std::cout << "[Герой] " << m_name << " потратил " << amount 
              << " маны. Осталось маны: " << m_mana << "\n";
    return true;
}

bool Hero::SpendGold(int amount)
{
    if (amount <= 0)
    {
        return false;
    }

    if (m_gold < amount)
    {
        std::cout << "[Герой] " << m_name << ": Недостаточно золота! (Нужно: " 
                  << amount << ", Есть: " << m_gold << ")\n";
        return false;
    }

    m_gold -= amount;
    std::cout << "[Герой] " << m_name << " потратил " << amount 
              << " золота. Осталось золота: " << m_gold << "\n";
    return true;
}

void Hero::EarnGold(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    m_gold += amount;
    std::cout << "[Герой] " << m_name << " получил " << amount 
              << " золота. Всего золота: " << m_gold << "\n";
}

bool Hero::PickUpItem(Item* item)
{
    std::cout << "[Герой] " << m_name << " пытается подобрать предмет...\n";
    return m_inventory.AddItem(item);
}

bool Hero::DropItem(std::size_t index)
{
    std::cout << "[Герой] " << m_name << " выбрасывает предмет из слота " << index << "...\n";
    return m_inventory.RemoveItem(index);
}

void Hero::Inspect() const
{
    std::cout << "========================================\n";
    std::cout << "Герой: " << m_name 
              << " | ХП: " << m_health 
              << " | Мана: " << m_mana 
              << " | Золото: " << m_gold << "\n";
    m_inventory.PrintItems();
    std::cout << "========================================\n";
}

} // namespace game
