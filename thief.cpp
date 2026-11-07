//
// ФАЙЛ thief.cpp
//

#include "thief.hpp"

#include <iostream>

namespace game
{

Thief::Thief()
    : BaseHero{ "Безымянный вор", 110, 30, 25, 0 }
{
    std::cout << "[Вор] Создан конструктором по умолчанию\n";
}

Thief::Thief(std::string_view name, int gold)
    : BaseHero{ name, 110, 30, 25, gold }
{
    std::cout << "[Вор] Создан: " << GetName() << "\n";
}

Thief::~Thief()
{
    std::cout << "[Вор] Уничтожен: " << (GetName().empty() ? "<перемещён>" : GetName()) << "\n";
}

int Thief::GetAttackDamage() const
{
    return BASE_DAMAGE;
}

std::unique_ptr<BaseHero> Thief::Clone() const
{
    return std::make_unique<Thief>(*this);
}

} // namespace game
