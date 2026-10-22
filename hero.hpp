//
// ФАЙЛ hero.hpp
//
#pragma once

#include "inventory.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>

namespace game
{

class Hero
{
public:
    Hero(std::string_view name, int health, int mana, int gold);
    Hero(const Hero&)            = delete;
    Hero(Hero&&)                 = delete;
    Hero& operator=(const Hero&) = delete;
    Hero& operator=(Hero&&)      = delete;
    ~Hero();

    void TakeDamage(int damage);
    bool UseMana(int amount);

    bool SpendGold(int amount);
    void EarnGold(int amount);

    bool PickUpItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<Item> DropItem(std::size_t index);

    bool EquipItem(std::size_t index);
    void ShowEquipped() const;

    void Inspect() const;

    [[nodiscard]] std::string_view GetName() const { return m_name; }
    [[nodiscard]] int GetHealth() const { return m_health; }
    [[nodiscard]] int GetMana() const { return m_mana; }
    [[nodiscard]] int GetGold() const { return m_gold; }
    [[nodiscard]] std::size_t GetInventorySize() const { return m_inventory.GetSize(); }

private:
    std::string m_name;
    int         m_health{ 100 };
    int         m_mana{ 50 };
    int         m_gold{ 0 };

    // Герой пользуется экипировкой, но не владеет ею: предмет может исчезнуть
    std::weak_ptr<Item> m_equipped;

    // Композиция: инвентарь по значению
    Inventory   m_inventory;
};

} // namespace game
