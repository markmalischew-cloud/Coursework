//
// ФАЙЛ item.cpp
//

#include "item.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>

namespace game
{

Item::Item(std::string_view name, ItemType type, ItemRarity rarity, int price)
    : m_name{ name }
    , m_type{ type }
    , m_rarity{ rarity }
    , m_price{ price }
{
    // Раньше неверные значения молча заменялись, теперь это исключение
    const bool isValidName = !m_name.empty()
        && std::all_of(m_name.begin(), m_name.end(), [](unsigned char ch)
    {
        return std::isalpha(ch) || ch == ' ' || ch >= 128;
    });

    if (!isValidName)
    {
        throw std::invalid_argument{ "некорректное название предмета" };
    }

    const auto typeValue = static_cast<int>(m_type);
    if (typeValue < 0 || typeValue > 3)
    {
        throw std::invalid_argument{ "неизвестный тип предмета" };
    }

    const auto rarityValue = static_cast<int>(m_rarity);
    if (rarityValue < 1 || rarityValue > 5)
    {
        throw std::invalid_argument{ "редкость предмета должна быть от 1 до 5" };
    }

    if (m_price < 0)
    {
        throw std::invalid_argument{ "цена предмета не может быть отрицательной" };
    }

    std::cout << "[Предмет] Создан: " << m_name << "\n";
}

Item::~Item() noexcept
{
    std::cout << "[Предмет] Уничтожен: " << m_name << "\n";
}

} // namespace game
