// 
// ФАЙЛ item.cpp
// 

#include <iostream>
#include "item.hpp"
#include <algorithm>
#include <cctype>

namespace game
{

Item::Item(std::string_view name, ItemType type, ItemRarity rarity, int price)
    : m_name{ name }
    , m_type{ type }
    , m_rarity{ rarity }
    , m_price{ price }
{

    bool isValid = std::all_of(m_name.begin(), m_name.end(), [](unsigned char ch)
    {
        return std::isalpha(ch) || ch == ' ' || ch >= 128;
    });

    if (!isValid || m_name.empty())
    {
        m_name = "Неизвестный предмет";
    }

    std::cout << "[Предмет] Создан: " << m_name << "\n";
 
    switch (m_type)
    {
        case ItemType::eWeapon:
        case ItemType::eArmor:
        case ItemType::eConsumable:
        case ItemType::eTreasure:
        break;

        default:
        m_type = ItemType::eTreasure;
        break;
    }
   


    if (m_price < 0)
    {
        m_price = 0;  
    }
    
    const auto rarityValue = static_cast<int>(m_rarity);
    if (rarityValue < 1 || rarityValue > 5)
    {
        m_rarity = ItemRarity::eCommon;
}

}

Item::~Item()
{
    std::cout << "[Предмет] Уничтожен: " << m_name << "\n";
}

} // namespace game
