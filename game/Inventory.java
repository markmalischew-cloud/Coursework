package game;

import java.util.ArrayList;
import java.util.List;

public class Inventory {
    private static final int CAPACITY = 20;

    private final List<Item> items = new ArrayList<>(CAPACITY);

    public Inventory() {
        System.out.println("[Инвентарь] Создан");
    }

    public boolean addItem(Item item) {
        if (item == null || items.size() >= CAPACITY || items.contains(item)) {
            System.out.println("[Инвентарь] Ошибка: не удалось добавить предмет!");
            return false;
        }
        items.add(item);
        return true;
    }

    public Item removeItem(int index) {
        if (index < 0 || index >= items.size()) {
            System.out.println("[Инвентарь] Ошибка: неверный индекс для удаления!");
            return null;
        }
        return items.remove(index);
    }

    public Item getItem(int index) {
        return index >= 0 && index < items.size() ? items.get(index) : null;
    }

    public int getSize() {
        return items.size();
    }

    public static int getCapacity() {
        return CAPACITY;
    }

    public void printItems() {
        System.out.println("--- Инвентарь (" + items.size() + "/" + CAPACITY + ") ---");
        for (int i = 0; i < items.size(); i++) {
            System.out.println(" Слот " + i + ": " + items.get(i).getName());
        }
    }

    @Override
    public String toString() {
        return "Инвентарь " + items.size() + "/" + CAPACITY;
    }
}
