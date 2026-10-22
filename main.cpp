//
// ФАЙЛ main.cpp
//

#include "item.hpp"
#include "inventory.hpp"
#include "hero.hpp"

#include <iostream>

int main()
{
    std::cout << "=== 1. СОЗДАНИЕ ПРЕДМЕТОВ ===\n\n";

    game::Item* sword = new game::Item("Экскалибур", game::ItemType::eWeapon, game::ItemRarity::eRare, 250);
    game::Item* potion = new game::Item("Зелье исцеления", game::ItemType::eConsumable, game::ItemRarity::eCommon, 50);
    game::Item* ring = new game::Item("Магическое кольцо", game::ItemType::eTreasure, game::ItemRarity::eLegendary, 1000);

    std::cout << "\n=== 2. СОЗДАНИЕ ГЕРОЯ И ТЕСТИРОВАНИЕ МЕХАНИК ===\n\n";

    {

        game::Hero hero("Arthas", 120, 80, 500);

        hero.Inspect();

        hero.PickUpItem(sword);
        hero.PickUpItem(potion);
        hero.PickUpItem(ring);

        hero.UseMana(30);
        hero.SpendGold(100);
        hero.EarnGold(50);

        hero.Inspect();

        hero.DropItem(1);

        hero.Inspect();

        std::cout << "\n--- Завершение области видимости (Герой уничтожается) ---\n";
        std::cout << "\n=== Композиция ===\n";
    }

    std::cout << "\n=== 3. ПРОВЕРКА ВРЕМЕНИ ЖИЗНИ (Агрегация) ===\n";

    delete sword;
    delete potion;
    delete ring;

    std::cout << "\n=== Программа успешно завершена ===\n";

    return 0;
}
