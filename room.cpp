//
// ФАЙЛ room.cpp
//

#include "room.hpp"

#include "base_hero.hpp"

#include <iostream>

namespace game
{

Room::Room(std::string_view name)
    : m_name{ name }
{
    std::cout << "[Комната] Создана: " << m_name << "\n";
}

Room::~Room()
{
    std::cout << "[Комната] Уничтожена: " << m_name << "\n";
}

void Room::Rename(std::string_view name)
{
    m_name = name;
    std::cout << "[Комната] Переименована в «" << m_name << "»\n";
}

void Room::Welcome(const BaseHero& hero) const
{
    std::cout << "[Комната] «" << m_name << "»: входит " << hero.GetFullTitle() << "\n";
}

} // namespace game
