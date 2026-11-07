//
// ФАЙЛ mage.cpp
//

#include "mage.hpp"

#include <iostream>

namespace game
{

Mage::Mage()
    : BaseHero{ "Безымянный маг", 80, 120, 5, 0 }
{
    std::cout << "[Маг] Создан конструктором по умолчанию\n";
}

Mage::Mage(std::string_view name, int gold)
    : BaseHero{ name, 80, 120, 5, gold }
{
    std::cout << "[Маг] Создан: " << GetName() << "\n";
}

Mage::~Mage()
{
    std::cout << "[Маг] Уничтожен: " << (GetName().empty() ? "<перемещён>" : GetName()) << "\n";
}

int Mage::GetAttackDamage() const
{
    return BASE_DAMAGE;
}

std::unique_ptr<BaseHero> Mage::Clone() const
{
    return std::make_unique<Mage>(*this);
}

std::string Mage::Describe() const
{
    // Базовая версия не вызывается; protected-метод Header() доступен наследнику
    return "Маг " + Header() + " | Мана: " + std::to_string(GetMana())
         + " | Бонус заклинаний: +" + std::to_string(SPELL_BONUS_PERCENT) + "%";
}

} // namespace game
