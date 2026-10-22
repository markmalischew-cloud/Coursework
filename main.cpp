//
// ФАЙЛ main.cpp
//

#include "hero.hpp"
#include "inventory.hpp"
#include "item.hpp"

#include <iostream>
#include <memory>
#include <utility>

namespace
{

void DemoUniquePtr()
{
    std::cout << "\n=== 4. unique_ptr: один владелец ===\n";

    {
        std::cout << "-- вход в блок\n";
        const auto hero = std::make_unique<game::Hero>("Артур", 100, 50, 30);
        hero->Inspect();
        std::cout << "-- выход из блока\n";
    }
    std::cout << "-- блок завершён, освобождать память вручную не пришлось\n";

    auto first = std::make_unique<game::Hero>("Марк", 70, 120, 10);
    std::cout << "first: " << (first ? "владеет героем" : "пуст") << "\n";

    auto second = std::move(first);
    std::cout << "после std::move\n";
    std::cout << "first:  " << (first ? "владеет героем" : "пуст") << "\n";
    std::cout << "second: " << (second ? "владеет героем" : "пуст") << "\n";
    std::cout << "-- конец функции\n";
}

void DemoSharedPtr()
{
    std::cout << "\n=== 5. shared_ptr: несколько владельцев ===\n";

    auto shield = std::make_shared<game::Item>("Щит стража", game::ItemType::eArmor,
                                               game::ItemRarity::eUncommon, 120);
    std::cout << "владельцев: " << shield.use_count() << "\n";

    {
        game::Hero hero{ "Эльза", 120, 40, 100 };
        hero.PickUpItem(shield);
        std::cout << "герой подобрал, владельцев: " << shield.use_count() << "\n";

        {
            const auto copy = shield;
            std::cout << "создана копия, владельцев: " << shield.use_count() << "\n";
        }
        std::cout << "копия уничтожена, владельцев: " << shield.use_count() << "\n";

        shield.reset();
        std::cout << "main отказался от предмета, но сумка героя его держит\n";
        hero.Inspect();

        std::cout << "-- конец блока: герой уничтожается вместе с инвентарём\n";
    }
    std::cout << "-- блок завершён\n";
}

void DemoWeakPtr()
{
    std::cout << "\n=== 6. weak_ptr: наблюдатель ===\n";

    auto axe = std::make_shared<game::Item>("Боевой топор", game::ItemType::eWeapon,
                                            game::ItemRarity::eRare, 90);
    const std::weak_ptr<game::Item> watcher = axe;
    std::cout << "создан weak_ptr, владельцев: " << axe.use_count() << "\n";

    game::Hero hero{ "Брунгильда", 150, 10, 60 };
    hero.PickUpItem(axe);
    hero.EquipItem(0);
    std::cout << "герой экипировал, владельцев: " << axe.use_count()
              << " (weak_ptr счётчик не увеличил)\n";
    hero.ShowEquipped();

    axe.reset();
    std::cout << "main отказался от предмета, но инвентарь его держит\n";
    hero.ShowEquipped();

    if (const auto locked = watcher.lock())
    {
        std::cout << "watcher.lock(): предмет жив, владельцев: " << locked.use_count() << "\n";
    }

    hero.DropItem(0);
    std::cout << "предмет выброшен, последний владелец исчез\n";

    hero.ShowEquipped();
    if (const auto locked = watcher.lock())
    {
        std::cout << "watcher.lock(): предмет жив\n";
    }
    else
    {
        std::cout << "watcher.lock(): пустой указатель, предмет уничтожен expired: "
                  << std::boolalpha << watcher.expired() << ")\n";
    }
    std::cout << "-- конец функции\n";
}

} // namespace

int main()
{
    std::cout << "=== 1. СОЗДАНИЕ ПРЕДМЕТОВ ===\n\n";

    auto sword  = std::make_shared<game::Item>("Экскалибур", game::ItemType::eWeapon,
                                               game::ItemRarity::eRare, 250);
    auto potion = std::make_shared<game::Item>("Зелье исцеления", game::ItemType::eConsumable,
                                               game::ItemRarity::eCommon, 50);
    auto ring   = std::make_shared<game::Item>("Магическое кольцо", game::ItemType::eTreasure,
                                               game::ItemRarity::eLegendary, 1000);

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
    std::cout << "Герой уничтожен, но предметы живы, их держит main:\n";
    std::cout << "  " << sword->GetName() << " (владельцев: " << sword.use_count() << ")\n";
    std::cout << "  " << potion->GetName() << " (владельцев: " << potion.use_count() << ")\n";
    std::cout << "  " << ring->GetName() << " (владельцев: " << ring.use_count() << ")\n\n";

    sword.reset();
    potion.reset();
    ring.reset();

    DemoUniquePtr();
    DemoSharedPtr();
    DemoWeakPtr();

    std::cout << "\n=== Программа успешно завершена ===\n";

    return 0;
}
