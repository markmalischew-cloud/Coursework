package game;

import java.lang.ref.WeakReference;

public class MemoryDemo {
    private MemoryDemo() {
    }

    public static void referencesAndCopies() {
        System.out.println("\n=== Ссылки и копии ===");
        Hero first = new Hero("Артур", 100, 30, 50);
        Hero second = first;
        second.takeDamage(30);
        System.out.println("first:  " + first);
        System.out.println("second: " + second);
        System.out.println("first == second: " + (first == second));
    }

    public static void resourceRelease() {
        System.out.println("\n=== Освобождение ресурса ===");
        AdventureLog kept;
        try (AdventureLog log = new AdventureLog("Подземелье, комната 1")) {
            kept = log;
            Hero hero = new Hero("Бродяга", 80, 20, 10);
            log.write("герой " + hero.getName() + " вошёл в комнату");
            hero.takeDamage(15);
            log.write("получен урон, здоровье: " + hero.getHealth());
        }
        System.out.println("После блока журнал закрыт: " + kept.isClosed()
                + ". Ресурс освобождён, но сам объект ещё существует.");
    }

    private static WeakReference<Item> createTemporary() {
        Item temp = new Item("Списанный меч", ItemType.WEAPON, ItemRarity.COMMON, 1);
        return new WeakReference<>(temp);
    }

    public static void garbageCollection() throws InterruptedException {
        System.out.println("\n=== Сборщик мусора ===");
        WeakReference<Item> watcher = createTemporary();
        System.out.println("Метод завершён, ссылок на предмет нет. Жив ли объект: "
                + (watcher.get() != null));
        for (int attempt = 1; attempt <= 5 && watcher.get() != null; attempt++) {
            System.gc(); 
            Thread.sleep(100);
        }
        System.out.println("После System.gc(). Жив ли объект: " + (watcher.get() != null));
    }
}
