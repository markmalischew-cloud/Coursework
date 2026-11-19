package game;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        demoInterface();
        demoMultipleInheritance();
        demoBinding();
        demoDynamicCast();
        demoConfiguration();
        demoComparable();
        demoExceptions();

        System.out.println("\n=== Программа успешно завершена ===");
    }

    private static void demoInterface() {
        System.out.println("\n=== 1. ИНТЕРФЕЙС Combatant ===\n");

        Warrior conan = new Warrior("Конан", 100);
        Monster goblin = new Monster("Гоблин", 100, 12, new AggressiveTactic());

        System.out.println("\n-- Combat.attack() знает только контракт Combatant:");
        Combat.attack(conan, goblin); // герой бьёт монстра
        Combat.attack(goblin, conan); // монстр бьёт героя

        System.out.println("\n-- конец функции");
    }

    private static void demoMultipleInheritance() {
        System.out.println("\n=== 2. МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===\n");

        Mage merlin = new Mage("Мерлин", 40);

        // Один и тот же объект, три разных взгляда на него
        BaseHero    asHero      = merlin;
        Combatant   asCombatant = merlin;
        SpellCaster asCaster    = merlin;

        System.out.println("\nкак BaseHero:     " + asHero.getFullTitle());
        System.out.println("как Combatant:    удар " + asCombatant.getAttackDamage());
        System.out.print("как SpellCaster:  ");
        int damage = asCaster.castSpell(SpellElement.FIRE);
        System.out.println("заклинание нанесло " + damage);

        System.out.println("\n-- конец функции");
    }

    private static void demoBinding() {
        System.out.println("\n=== 3. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ ===\n");

        Warrior warrior = new Warrior("Конан", 100);
        BaseHero hero = warrior; // ссылка на базовый класс, внутри воин

        // В Java все ОБЫЧНЫЕ методы виртуальны, поэтому "раннее связывание"
        // получают только static / private / final методы.
        // Здесь используем static: он выбирается по ТИПУ КЛАССА/ССЫЛКИ.
        System.out.println("getKind() — static, раннее связывание:");
        System.out.println("  через Warrior:  " + Warrior.getKind());
        System.out.println("  через BaseHero: " + BaseHero.getKind()
                + "   (раннее: выбрано по типу класса)");

        // Обычный метод — позднее связывание по настоящему типу объекта
        System.out.println("getClassName() — обычный (виртуальный) метод, позднее связывание:");
        System.out.println("  через warrior:  " + warrior.getClassName());
        System.out.println("  через BaseHero: " + hero.getClassName()
                + "   (позднее: выбрано по типу объекта)");

        System.out.println("\n-- конец функции");
    }

    private static void demoDynamicCast() {
        System.out.println("\n=== 4. ПРОВЕРКА ТИПА: instanceof ===\n");

        Mage merlin = new Mage("Мерлин", 40);
        Monster ogre = new Monster("Огр", 150, 20, new AggressiveTactic());

        System.out.println("\n-- герой реализует SpellCaster, колдует:");
        Combat.castSpellAt(merlin, ogre, SpellElement.FIRE);

        System.out.println("\n-- монстр не реализует SpellCaster, instanceof == false:");
        Combat.castSpellAt(ogre, merlin, SpellElement.FIRE);

        System.out.println("\n-- конец функции");
    }

    private static void demoConfiguration() {
        System.out.println("\n=== 5. КОНФИГУРИРОВАНИЕ: ТАКТИКА МОНСТРА ===\n");

        System.out.println("-- статическое: тактика задана при создании");
        Monster brave = new Monster("Храбрый гоблин", 100, 10, new AggressiveTactic());
        Monster timid = new Monster("Робкий гоблин", 100, 10, new CowardlyTactic(40));

        Warrior conan = new Warrior("Конан", 100);
        for (int i = 0; i < 3; ++i) {
            Combat.attack(conan, brave);
            Combat.attack(conan, timid);
        }

        System.out.println("\nздоровье обоих: " + brave.getHealthPercent() + "%");
        System.out.println(brave.getName() + " (" + brave.getTacticName() + "): "
                + brave.chooseAction().getTitle());
        System.out.println(timid.getName() + " (" + timid.getTacticName() + "): "
                + timid.chooseAction().getTitle());

        System.out.println("\n-- динамическое: тактика меняется во время боя, здоровье то же");
        brave.setTactic(new CowardlyTactic(40));
        System.out.println(brave.getName() + ": " + brave.chooseAction().getTitle());

        brave.setTactic(new BeggingTactic(40));
        System.out.println(brave.getName() + ": " + brave.chooseAction().getTitle());

        System.out.println("\n-- конец функции");
    }

    private static void demoComparable() {
        System.out.println("\n=== 6. СТАНДАРТНЫЙ ИНТЕРФЕЙС Comparable ===\n");

        BaseHero[] heroes = {
            new Mage("Мерлин", 0),
            new Warrior("Конан", 0),
            new Thief("Алиса", 0),
        };

        System.out.println("-- до сортировки:");
        for (BaseHero h : heroes) System.out.println("  " + h.getFullTitle());

        // Arrays.sort работает только через Comparable: о конкретных классах не знает
        Arrays.sort(heroes);

        System.out.println("-- после Arrays.sort (по имени):");
        for (BaseHero h : heroes) System.out.println("  " + h.getFullTitle());

        System.out.println("\n-- конец функции");
    }

    private static void demoExceptions() {
        System.out.println("\n=== 7. ИСКЛЮЧЕНИЯ ===\n");

        System.out.println("-- неверные данные при создании героя:");
        try {
            new Warrior("", 100);
        } catch (IllegalArgumentException e) {
            System.out.println("Не удалось создать героя: " + e.getMessage());
        }

        System.out.println("\n-- нехватка маны (правило 5):");
        Warrior conan = new Warrior("Конан", 100);
        Monster dummy = new Monster("Манекен", 200, 0, new AggressiveTactic());

        try {
            Combat.castSpellAt(conan, dummy, SpellElement.FIRE); // нужно 80 маны, есть 30
            System.out.println("(этой строки не будет)");
        } catch (NotEnoughManaException e) {          // частный — первым
            System.out.println("Ход пропущен: " + e.getMessage());
        } catch (GameException e) {                   // общий
            System.out.println("Нарушено правило игры: " + e.getMessage());
        } catch (RuntimeException e) {                // ещё более общий
            System.out.println("Ошибка: " + e.getMessage());
        }
        System.out.println("мана после неудачи: " + conan.getMana() + " (не изменилась)");

        System.out.println("\n-- герой выбирает заклинание подешевле:");
        try {
            Combat.castSpellAt(conan, dummy, SpellElement.WATER);
        } catch (GameException e) {
            System.out.println("Нарушено правило игры: " + e.getMessage());
        }

        System.out.println("\n-- нехватка золота:");
        try {
            conan.spendGold(500);
        } catch (NotEnoughGoldException e) {
            System.out.println("Покупка не удалась: " + e.getMessage());
        }
        conan.spendGold(30);

        System.out.println("\n-- смена экипировки в бою (правило 3):");
        Item sword = new Item("Стальной меч", Item.Type.WEAPON, Item.Rarity.RARE, 80);
        conan.pickUpItem(sword);
        conan.enterCombat();
        try {
            conan.equipItem(0);
        } catch (ForbiddenInCombatException e) {
            System.out.println("Отказано: " + e.getMessage());
        }
        conan.leaveCombat();
        conan.equipItem(0);

        System.out.println("\n-- неверный слот и повторный предмет:");
        try {
            conan.dropItem(5);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Ошибка слота: " + e.getMessage());
        }
        try {
            conan.pickUpItem(sword);
        } catch (IllegalArgumentException e) {
            System.out.println("Ошибка предмета: " + e.getMessage());
        }

        System.out.println("\n-- неверные данные предмета:");
        try {
            new Item("Меч123", Item.Type.WEAPON, Item.Rarity.COMMON, 10);
        } catch (IllegalArgumentException e) {
            System.out.println("Не удалось создать предмет: " + e.getMessage());
        }

        // try-with-resources: ресурс освобождается при любом исходе
        System.out.println("\n-- try-with-resources (журнал закрывается автоматически):");
        try (BattleLog log = new BattleLog()) {
            log.write("попытка выдачи");
            Combat.attack(conan, dummy);
        } // close() вызовется и при успехе, и при исключении

        System.out.println("\n-- конец функции");
    }
}
