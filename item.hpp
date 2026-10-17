//
// ФАЙЛ item.hpp
// 
#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace game
{

enum class ItemType
{
    eWeapon,
    eArmor,
    eConsumable,
    eTreasure
};

enum class ItemRarity
{
    eCommon = 1,
    eUncommon = 2,
    eRare = 3,
    eEpic = 4,
    eLegendary = 5
};

class Item
{
public:
    Item(std::string_view name, ItemType type, ItemRarity rarity, int price);
    Item(const Item&)            = delete;
    Item(Item&&)                 = delete;  
    Item& operator=(const Item&) = delete;  
    Item& operator=(Item&&)      = delete;  
    ~Item();

    [[nodiscard]] std::string_view GetName() const
    {
        return m_name;
    }

    [[nodiscard]] ItemType GetType() const
    {
        return m_type;
    }
           
    [[nodiscard]] ItemRarity GetRarity() const
    {
        return m_rarity;
    }
       
    [[nodiscard]] int GetPrice() const
    {
        return m_price;
    }

private:
    std::string m_name{};
    ItemType    m_type{};
    ItemRarity  m_rarity{};
    int         m_price{ 0 };
};

} // namespace game
