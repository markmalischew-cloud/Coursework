//
// ФАЙЛ warrior.cpp
//

#include "warrior.hpp"

#include <iostream>

namespace game
{

Warrior::Warrior()
    : BaseHero{ "Безымянный воин", 150, 30, 5, 0 }
{
    std::cout << "[Воин] Создан конструктором по умолчанию\n";
}

Warrior::Warrior(std::string_view name, int gold)
    : BaseHero{ name, 150, 30, 5, gold } // сначала — базовая часть
{
    std::cout << "[Воин] Создан: " << GetName() << "\n";
}

Warrior::~Warrior()
{
    std::cout << "[Воин] Уничтожен: " << (GetName().empty() ? "<перемещён>" : GetName()) << "\n";
}

int Warrior::GetAttackDamage() const
{
    return BASE_DAMAGE * (100 + WEAPON_BONUS_PERCENT) / 100;
}

std::unique_ptr<BaseHero> Warrior::Clone() const
{
    return std::make_unique<Warrior>(*this);
}

std::string Warrior::Describe() const
{
    return BaseHero::Describe() + " | Бонус классового оружия: +"
         + std::to_string(WEAPON_BONUS_PERCENT) + "%";
}

} // namespace game
