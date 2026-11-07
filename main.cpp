//
// ФАЙЛ main.cpp
//

#include "base_hero.hpp"
#include "item.hpp"
#include "mage.hpp"
#include "room.hpp"
#include "thief.hpp"
#include "warrior.hpp"

#include <iostream>
#include <memory>
#include <utility>

namespace
{

void DemoConstructors()
{
    std::cout << "\n=== 1. КОНСТРУКТОРЫ И ПОРЯДОК ВЫЗОВОВ ===\n";

    std::cout << "\n-- по умолчанию:\n";
    game::Warrior wanderer;

    std::cout << "\n-- с параметрами (конструктор базы вызывается в списке инициализации):\n";
    game::Mage merlin{ "Мерлин", 40 };

    std::cout << "\n-- копирования:\n";
    game::Mage twin = merlin;
    std::cout << "номера: оригинал №" << merlin.GetId() << ", копия №" << twin.GetId() << "\n";

    std::cout << "\n-- перемещения:\n";
    const game::Mage moved = std::move(twin);
    std::cout << "перемещённый герой сохранил №" << moved.GetId()
              << ", прежний объект опустошён (имя: «" << twin.GetName() << "»)\n";

    std::cout << "\n-- конец функции: деструкторы в порядке, обратном созданию:\n";
}

void DemoProtected()
{
    std::cout << "\n=== 2. PROTECTED ===\n";

    const game::Thief shadow{ "Тень", 15 };
    std::cout << shadow.Describe() << "\n";

    // shadow.Header();        // ошибка компиляции: Header() объявлен protected
    // game::BaseHero hero;    // ошибка компиляции: класс абстрактный, конструкторы protected
    std::cout << "Header() доступен наследникам внутри Describe(), снаружи его не вызвать\n";
}

void DemoVirtualDestructor()
{
    std::cout << "\n=== 3. ВИРТУАЛЬНЫЙ ДЕСТРУКТОР ===\n";

    std::unique_ptr<game::BaseHero> hero = std::make_unique<game::Warrior>("Конан", 100);
    std::cout << "-- уничтожаем через указатель на базовый класс:\n";
    hero.reset();
    std::cout << "-- вызваны оба деструктора: наследника, затем базы\n";
}

void DemoCopying()
{
    std::cout << "\n=== 4. ПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ ===\n";

    const auto room   = std::make_shared<game::Room>("Зал стражей");
    const auto sword  = std::make_shared<game::Item>("Стальной меч", game::ItemType::eWeapon,
                                                     game::ItemRarity::eRare, 80);
    const auto potion = std::make_shared<game::Item>("Зелье исцеления", game::ItemType::eConsumable,
                                                     game::ItemRarity::eCommon, 15);

    game::Warrior original{ "Конан", 100 };
    original.EnterRoom(room);
    original.PickUpItem(sword);

    std::cout << "\n-- копирование: Warrior copy = original\n";
    game::Warrior copy = original;
    std::cout << "владельцев комнаты: " << room.use_count() << " (main, оригинал, копия)\n";

    std::cout << "\n-- ПОВЕРХНОСТНАЯ копия (комната общая): переименовываем через копию\n";
    copy.RenameRoom("Тронный зал");
    std::cout << "оригинал: " << original.Describe() << "\n";
    std::cout << "копия:    " << copy.Describe() << "\n";

    std::cout << "\n-- ГЛУБОКАЯ копия (инвентарь свой): копия подбирает зелье\n";
    copy.PickUpItem(potion);
    std::cout << "предметов у оригинала: " << original.GetInventorySize()
              << ", у копии: " << copy.GetInventorySize() << "\n";
    std::cout << "(сами предметы общие, поэтому у меча владельцев: " << sword.use_count() << ")\n";

    std::cout << "\n-- глубокая копия через Clone() по указателю на базовый класс:\n";
    const std::unique_ptr<game::BaseHero> hero = std::make_unique<game::Thief>("Тень", 15);
    const std::unique_ptr<game::BaseHero> twin = hero->Clone();
    std::cout << "оригинал №" << hero->GetId() << ", клон №" << twin->GetId()
              << ", класс клона: " << twin->GetClassName() << "\n";

    std::cout << "\n-- конец функции\n";
}

void DemoOverride()
{
    std::cout << "\n=== 5. ПЕРЕОПРЕДЕЛЕНИЕ ===\n";

    const game::Warrior warrior{ "Конан", 100 };
    const game::Mage mage{ "Мерлин", 40 };
    const game::Thief thief{ "Тень", 15 };

    std::cout << "\nВоин (дополняет базовый Describe, BaseHero::Describe() вызывается):\n"
              << warrior.Describe() << "\n";
    std::cout << "\nМаг (заменяет полностью, базовый Describe не вызывается):\n"
              << mage.Describe() << "\n";
    std::cout << "\nВор (не переопределяет, используется базовый Describe):\n"
              << thief.Describe() << "\n";
    std::cout << "\n";
}

void DemoStrings()
{
    std::cout << "\n=== 6. СТРОКИ ===\n";

    game::Warrior hero{ "Конан Варвар", 50 };
    const auto sword = std::make_shared<game::Item>("Стальной меч", game::ItemType::eWeapon,
                                                    game::ItemRarity::eRare, 80);
    hero.PickUpItem(sword);

    std::cout << "\nКонкатенация:      " << hero.GetFullTitle() << "\n";
    std::cout << "find + substr:     короткое имя «" << hero.GetShortName() << "»\n";
    std::cout << "сравнение:         IsNamed(\"Конан Варвар\") = " << std::boolalpha
              << hero.IsNamed("Конан Варвар") << ", IsNamed(\"Конан\") = "
              << hero.IsNamed("Конан") << "\n";

    if (const auto index = hero.FindItem("меч"))
    {
        std::cout << "find в названиях:  «меч» найден в слоте " << *index << "\n";
    }
    if (!hero.FindItem("щит"))
    {
        std::cout << "find в названиях:  «щит» не найден\n";
    }
    std::cout << "\n";
}

void DemoThis()
{
    std::cout << "\n=== 7. THIS ===\n";

    game::Mage a{ "Альфа", 10 };
    game::Mage b{ "Бета", 20 };
    game::Mage c{ "Гамма", 30 };

    std::cout << "\n-- возврат *this позволяет цепочку: a = b = c\n";
    a = b = c;
    std::cout << "имя a после цепочки: " << a.GetName() << " (номер остался №" << a.GetId() << ")\n";

    std::cout << "\n-- проверка самоприсваивания:\n";
    const game::Mage& alias = a;
    a = alias;

    std::cout << "\n-- передача текущего объекта другому объекту (комнате):\n";
    const auto room = std::make_shared<game::Room>("Подвал");
    a.EnterRoom(room);

    std::cout << "\n-- конец функции\n";
}

void DemoStatic()
{
    std::cout << "\n=== 8. СТАТИЧЕСКИЕ ЧЛЕНЫ ===\n";

    std::cout << "создано героев на данный момент: " << game::BaseHero::GetCreatedCount() << "\n";
    const game::Thief thief{ "Новичок", 0 };
    std::cout << "после ещё одного героя: " << game::BaseHero::GetCreatedCount()
              << " (номер новичка №" << thief.GetId() << ")\n";
    std::cout << "\n";
}

void DemoPolymorphicArray()
{
    std::cout << "\n=== 9. МАССИВ unique_ptr<BaseHero> ===\n\n";

    std::unique_ptr<game::BaseHero> party[3];
    party[0] = std::make_unique<game::Warrior>("Конан", 100);
    party[1] = std::make_unique<game::Mage>("Мерлин", 40);
    party[2] = std::make_unique<game::Thief>("Тень", 15);

    const auto ring = std::make_shared<game::Item>("Магическое кольцо", game::ItemType::eTreasure,
                                                   game::ItemRarity::eLegendary, 1000);
    party[2]->PickUpItem(ring);

    std::cout << "\n-- работа через указатель на базовый класс:\n";
    for (const auto& hero : party)
    {
        std::cout << hero->GetFullTitle() << ": удар " << hero->GetAttackDamage()
                  << ", удача " << hero->GetLuck() << ", здоровье " << hero->GetHealth() << "\n";
        hero->TakeDamage(10);
    }

    std::cout << "\n-- полное описание каждого:\n";
    for (const auto& hero : party)
    {
        std::cout << hero->Describe() << "\n";
    }

    std::cout << "\n-- конец функции: массив уничтожает героев через базовый указатель\n";
}

} // namespace

int main()
{
    DemoConstructors();
    DemoProtected();
    DemoVirtualDestructor();
    DemoCopying();
    DemoOverride();
    DemoStrings();
    DemoThis();
    DemoStatic();
    DemoPolymorphicArray();

    std::cout << "\n=== Программа успешно завершена ===\n";
    return 0;
}
