//
// ФАЙЛ main.cpp
//

#include "combat.hpp"
#include "game_error.hpp"
#include "i_combatant.hpp"
#include "i_spell_caster.hpp"
#include "item.hpp"
#include "mage.hpp"
#include "monster.hpp"
#include "monster_tactics.hpp"
#include "thief.hpp"
#include "warrior.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace
{

void DemoInterface()
{
    std::cout << "\n=== 1. ИНТЕРФЕЙС ICombatant ===\n\n";

    game::Warrior conan{ "Конан", 100 };
    game::Monster goblin{ "Гоблин", 100, 12, std::make_unique<game::AggressiveTactic>() };

    std::cout << "\n-- Attack() знает только контракт ICombatant:\n";
    game::Attack(conan, goblin);   // герой бьёт монстра
    game::Attack(goblin, conan);   // монстр бьёт героя

    std::cout << "\n-- конец функции\n";
}

void DemoMultipleInheritance()
{
    std::cout << "\n=== 2. МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===\n\n";

    game::Mage merlin{ "Мерлин", 40 };

    // Один и тот же объект, три разных взгляда на него
    game::BaseHero&     asHero      = merlin;
    game::ICombatant&   asCombatant = merlin;
    game::ISpellCaster& asCaster    = merlin;

    std::cout << "\nкак BaseHero:     " << asHero.GetFullTitle() << "\n";
    std::cout << "как ICombatant:   удар " << asCombatant.GetAttackDamage() << "\n";
    std::cout << "как ISpellCaster: ";
    const int damage = asCaster.CastSpell(game::SpellElement::eFire);
    std::cout << "заклинание нанесло " << damage << "\n";

    std::cout << "\n-- конец функции\n";
}

void DemoBinding()
{
    std::cout << "\n=== 3. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ ===\n\n";

    game::Warrior warrior{ "Конан", 100 };
    game::BaseHero& hero = warrior;   // ссылка на базовый класс, внутри воин

    std::cout << "\nGetKind() невиртуальный:\n";
    std::cout << "  через Warrior:   " << warrior.GetKind() << "\n";
    std::cout << "  через BaseHero&: " << hero.GetKind() << "   (раннее: выбрано по типу ссылки)\n";

    std::cout << "GetClassName() виртуальный:\n";
    std::cout << "  через Warrior:   " << warrior.GetClassName() << "\n";
    std::cout << "  через BaseHero&: " << hero.GetClassName() << "   (позднее: выбрано по типу объекта)\n";

    std::cout << "\n-- конец функции\n";
}

void DemoDynamicCast()
{
    std::cout << "\n=== 4. ПРОВЕРКА ТИПА: dynamic_cast ===\n\n";

    game::Mage merlin{ "Мерлин", 40 };
    game::Monster ogre{ "Огр", 150, 20, std::make_unique<game::AggressiveTactic>() };

    std::cout << "\n-- герой реализует ISpellCaster, колдует:\n";
    game::CastSpellAt(merlin, ogre, game::SpellElement::eFire);

    std::cout << "\n-- монстр не реализует ISpellCaster, dynamic_cast вернул nullptr:\n";
    game::CastSpellAt(ogre, merlin, game::SpellElement::eFire);

    std::cout << "\n-- конец функции\n";
}

void DemoConfiguration()
{
    std::cout << "\n=== 5. КОНФИГУРИРОВАНИЕ: ТАКТИКА МОНСТРА ===\n\n";

    std::cout << "-- статическое: тактика задана при создании\n";
    game::Monster brave{ "Храбрый гоблин", 100, 10, std::make_unique<game::AggressiveTactic>() };
    game::Monster timid{ "Робкий гоблин", 100, 10, std::make_unique<game::CowardlyTactic>(40) };

    game::Warrior conan{ "Конан", 100 };
    for (int i = 0; i < 3; ++i)
    {
        game::Attack(conan, brave);
        game::Attack(conan, timid);
    }

    std::cout << "\nздоровье обоих: " << brave.GetHealthPercent() << "%\n";
    std::cout << brave.GetName() << " (" << brave.GetTacticName() << "): "
              << game::ToString(brave.ChooseAction()) << "\n";
    std::cout << timid.GetName() << " (" << timid.GetTacticName() << "): "
              << game::ToString(timid.ChooseAction()) << "\n";

    std::cout << "\n-- динамическое: тактика меняется во время боя, здоровье то же\n";
    brave.SetTactic(std::make_unique<game::CowardlyTactic>(40));
    std::cout << brave.GetName() << ": " << game::ToString(brave.ChooseAction()) << "\n";

    brave.SetTactic(std::make_unique<game::BeggingTactic>(40));
    std::cout << brave.GetName() << ": " << game::ToString(brave.ChooseAction()) << "\n";

    std::cout << "\n-- конец функции\n";
}

void DemoExceptions()
{
    std::cout << "\n=== 6. ИСКЛЮЧЕНИЯ ===\n";

    std::cout << "\n-- неверные данные при создании героя:\n";
    try
    {
        game::Warrior broken{ "", 100 };
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Не удалось создать героя: " << error.what() << "\n";
    }

    std::cout << "\n-- нехватка маны (правило 5):\n";
    game::Warrior conan{ "Конан", 100 };
    game::Monster dummy{ "Манекен", 200, 0, std::make_unique<game::AggressiveTactic>() };

    try
    {
        game::CastSpellAt(conan, dummy, game::SpellElement::eFire);   // нужно 80 маны, есть 30
        std::cout << "(этой строки не будет)\n";
    }
    catch (const game::NotEnoughManaError& error)
    {
        std::cout << "Ход пропущен: " << error.what() << "\n";
    }
    catch (const game::GameError& error)
    {
        std::cout << "Нарушено правило игры: " << error.what() << "\n";
    }
    catch (const std::exception& error)
    {
        std::cout << "Ошибка: " << error.what() << "\n";
    }
    std::cout << "мана после неудачи: " << conan.GetMana() << " (не изменилась)\n";

    std::cout << "\n-- герой выбирает заклинание подешевле:\n";
    try
    {
        game::CastSpellAt(conan, dummy, game::SpellElement::eWater);
    }
    catch (const game::GameError& error)
    {
        std::cout << "Нарушено правило игры: " << error.what() << "\n";
    }

    std::cout << "\n-- нехватка золота:\n";
    try
    {
        conan.SpendGold(500);
    }
    catch (const game::NotEnoughGoldError& error)
    {
        std::cout << "Покупка не удалась: " << error.what() << "\n";
    }
    conan.SpendGold(30);

    std::cout << "\n-- смена экипировки в бою (правило 3):\n";
    const auto sword = std::make_shared<game::Item>("Стальной меч", game::ItemType::eWeapon,
                                                    game::ItemRarity::eRare, 80);
    conan.PickUpItem(sword);
    conan.EnterCombat();
    try
    {
        conan.EquipItem(0);
    }
    catch (const game::ForbiddenInCombatError& error)
    {
        std::cout << "Отказано: " << error.what() << "\n";
    }
    conan.LeaveCombat();
    conan.EquipItem(0);

    std::cout << "\n-- неверный слот и повторный предмет:\n";
    try
    {
        const auto dropped = conan.DropItem(5);
    }
    catch (const std::out_of_range& error)
    {
        std::cout << "Ошибка слота: " << error.what() << "\n";
    }

    try
    {
        conan.PickUpItem(sword);
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Ошибка предмета: " << error.what() << "\n";
    }

    std::cout << "\n-- неверные данные предмета:\n";
    try
    {
        const game::Item bad{ "Меч123", game::ItemType::eWeapon, game::ItemRarity::eCommon, 10 };
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Не удалось создать предмет: " << error.what() << "\n";
    }

    std::cout << "\n-- конец функции\n";
}

} // namespace

int main()
{
    DemoInterface();
    DemoMultipleInheritance();
    DemoBinding();
    DemoDynamicCast();
    DemoConfiguration();
    DemoExceptions();

    std::cout << "\n=== Программа успешно завершена ===\n";
    return 0;
}
