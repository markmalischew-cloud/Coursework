package game;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("=== Композиция: герой создаёт инвентарь сам ===");
        Hero hero = new Hero("Эльза", 120, 40, 100);

        System.out.println("\n=== Агрегация: предметы созданы снаружи ===");
        Item sword = new Item("Стальной меч", ItemType.WEAPON, ItemRarity.RARE, 80);
        Item potion = new Item("Зелье исцеления", ItemType.CONSUMABLE, ItemRarity.COMMON, 15);
        hero.pickUpItem(sword);
        hero.pickUpItem(potion);
        hero.inspect();

        Item dropped = hero.dropItem(0);
        System.out.println("Выброшен, но жив: " + dropped);
        hero.inspect();

        System.out.println("\n=== Проверка правил ===");
        hero.pickUpItem(potion);          // дубликат
        hero.pickUpItem(null);            // пустая ссылка
        hero.dropItem(5);                 // неверный индекс
        hero.spendGold(500);              // не хватает золота
        new Item("Меч123", ItemType.WEAPON, ItemRarity.COMMON, -5); // плохое имя
        new Hero("", -10, -5, -1);        // плохие параметры героя

        MemoryDemo.referencesAndCopies();
        MemoryDemo.resourceRelease();
        MemoryDemo.garbageCollection();
    }
}
