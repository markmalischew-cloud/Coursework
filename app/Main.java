package app;

import game.BaseHero;
import game.Item;
import game.ItemRarity;
import game.ItemType;
import game.Mage;
import game.Room;
import game.Thief;
import game.Warrior;

import java.util.HashSet;
import java.util.Set;

public class Main {
    public static void main(String[] args) {
        demoConstructors();
        demoProtected();
        demoCopying();
        demoOverride();
        demoStrings();
        demoThis();
        demoStatic();
        demoEquals();
        demoPolymorphicArray();

        System.out.println("\n=== Программа успешно завершена ===");
    }

    private static void demoConstructors() {
        System.out.println("\n=== 1. КОНСТРУКТОРЫ И ПОРЯДОК ВЫЗОВОВ ===");

        System.out.println("\n-- по умолчанию (this(...) вызывает конструктор с параметрами):");
        Warrior wanderer = new Warrior();

        System.out.println("\n-- с параметрами (super(...) вызывает конструктор базы первой строкой):");
        Mage merlin = new Mage("Мерлин", 40);

        System.out.println("\n-- копирования:");
        Mage twin = new Mage(merlin);
        System.out.println("номера: оригинал №" + merlin.getId() + ", копия №" + twin.getId());
        System.out.println("один и тот же объект: " + (merlin == twin));
    }

    private static void demoProtected() {
        System.out.println("\n=== 2. PROTECTED ===");

        Thief shadow = new Thief("Тень", 15);
        System.out.println(shadow.describe());

        // shadow.header();   // ошибка компиляции: header() объявлен protected, а Main в другом пакете
        // new BaseHero(...); // ошибка компиляции: класс абстрактный, конструкторы protected
        System.out.println("header() доступен наследникам внутри describe(), из другого пакета его не вызвать");
    }

    private static void demoCopying() {
        System.out.println("\n=== 3. ПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ ===");

        Room room = new Room("Зал стражей");
        Item sword = new Item("Стальной меч", ItemType.WEAPON, ItemRarity.RARE, 80);
        Item potion = new Item("Зелье исцеления", ItemType.CONSUMABLE, ItemRarity.COMMON, 15);

        Warrior original = new Warrior("Конан", 100);
        original.enterRoom(room);
        original.pickUpItem(sword);

        System.out.println("\n-- копирование: new Warrior(original)");
        Warrior copy = new Warrior(original);

        System.out.println("\n-- ПОВЕРХНОСТНАЯ копия (комната общая): переименовываем через копию");
        copy.renameRoom("Тронный зал");
        System.out.println("оригинал: " + original.describe());
        System.out.println("копия:    " + copy.describe());

        System.out.println("\n-- ГЛУБОКАЯ копия (инвентарь свой): копия подбирает зелье");
        copy.pickUpItem(potion);
        System.out.println("предметов у оригинала: " + original.getInventorySize()
                + ", у копии: " + copy.getInventorySize());
        System.out.println("(сами предметы общие: меч у них один и тот же объект)");

        System.out.println("\n-- глубокая копия через copy() по ссылке на базовый класс:");
        BaseHero hero = new Thief("Тень", 15);
        BaseHero twin = hero.copy();
        System.out.println("оригинал №" + hero.getId() + ", копия №" + twin.getId()
                + ", класс копии: " + twin.getClassName());
    }

    private static void demoOverride() {
        System.out.println("\n=== 4. ПЕРЕОПРЕДЕЛЕНИЕ ===");

        Warrior warrior = new Warrior("Конан", 100);
        Mage mage = new Mage("Мерлин", 40);
        Thief thief = new Thief("Тень", 15);

        System.out.println("\nВоин (дополняет базовый describe, super.describe() вызывается):");
        System.out.println(warrior.describe());
        System.out.println("\nМаг (заменяет полностью, базовый describe не вызывается):");
        System.out.println(mage.describe());
        System.out.println("\nВор (не переопределяет, используется базовый describe):");
        System.out.println(thief.describe());
    }

    private static void demoStrings() {
        System.out.println("\n=== 5. СТРОКИ ===");

        Warrior hero = new Warrior("Конан Варвар", 50);
        Item sword = new Item("Стальной меч", ItemType.WEAPON, ItemRarity.RARE, 80);
        hero.pickUpItem(sword);

        System.out.println("\nКонкатенация:      " + hero.getFullTitle());
        System.out.println("indexOf + substring: короткое имя \"" + hero.getShortName() + "\"");
        System.out.println("сравнение:         isNamed(\"Конан Варвар\") = " + hero.isNamed("Конан Варвар")
                + ", isNamed(\"Конан\") = " + hero.isNamed("Конан"));

        int found = hero.findItem("меч");
        if (found >= 0) {
            System.out.println("поиск в названиях: \"меч\" найден в слоте " + found);
        }
        if (hero.findItem("щит") < 0) {
            System.out.println("поиск в названиях: \"щит\" не найден");
        }
    }

    private static void demoThis() {
        System.out.println("\n=== 6. THIS ===");

        Mage a = new Mage("Альфа", 10);
        Mage b = new Mage("Бета", 20);
        Mage c = new Mage("Гамма", 30);

        System.out.println("\n-- возврат this позволяет цепочку: a.copyStateFrom(b.copyStateFrom(c))");
        a.copyStateFrom(b.copyStateFrom(c));
        System.out.println("имя a после цепочки: " + a.getName() + " (номер остался №" + a.getId() + ")");

        System.out.println("\n-- проверка самоприсваивания:");
        a.copyStateFrom(a);

        System.out.println("\n-- передача текущего объекта другому объекту (комнате):");
        Room cellar = new Room("Подвал");
        a.enterRoom(cellar);
    }

    private static void demoStatic() {
        System.out.println("\n=== 7. СТАТИЧЕСКИЕ ЧЛЕНЫ ===");

        System.out.println("создано героев на данный момент: " + BaseHero.getCreatedCount());
        Thief newcomer = new Thief("Новичок", 0);
        System.out.println("после ещё одного героя: " + BaseHero.getCreatedCount()
                + " (номер новичка №" + newcomer.getId() + ")");
    }

    private static void demoEquals() {
        System.out.println("\n=== 8. EQUALS И HASHCODE ===");

        Warrior first = new Warrior("Конан", 100);
        Warrior second = new Warrior("Конан", 5);
        Warrior copy = new Warrior(first);
        Mage sameNameMage = new Mage("Конан", 0);

        System.out.println("\nfirst == second:          " + (first == second));
        System.out.println("first.equals(second):     " + first.equals(second));
        System.out.println("first.equals(copy):       " + first.equals(copy));
        System.out.println("first.equals(маг Конан):  " + first.equals(sameNameMage));
        System.out.println("hashCode равны:           " + (first.hashCode() == second.hashCode()));

        Set<BaseHero> set = new HashSet<>();
        set.add(first);
        set.add(second);
        set.add(copy);
        set.add(sameNameMage);
        System.out.println("в HashSet из четырёх героев: " + set.size());
    }

    private static void demoPolymorphicArray() {
        System.out.println("\n=== 9. МАССИВ BaseHero[] ===\n");

        BaseHero[] party = {
                new Warrior("Конан", 100),
                new Mage("Мерлин", 40),
                new Thief("Тень", 15)
        };

        Item ring = new Item("Магическое кольцо", ItemType.TREASURE, ItemRarity.LEGENDARY, 1000);
        party[2].pickUpItem(ring);

        System.out.println("\n-- работа через ссылку на базовый класс:");
        for (BaseHero hero : party) {
            System.out.println(hero.getFullTitle() + ": удар " + hero.getAttackDamage()
                    + ", удача " + hero.getLuck() + ", здоровье " + hero.getHealth());
            hero.takeDamage(10);
        }

        System.out.println("\n-- полное описание каждого:");
        for (BaseHero hero : party) {
            System.out.println(hero);
        }
    }
}
