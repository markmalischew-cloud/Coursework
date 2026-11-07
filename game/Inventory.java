package game;

import java.util.ArrayList;
import java.util.List;

public class Inventory {
    private static final int CAPACITY = 20;

    // Агрегация: предметы создаются снаружи, инвентарь хранит только ссылки
    private final List<Item> items;

    public Inventory() {
        this.items = new ArrayList<>(CAPACITY);
        System.out.println("[Инвентарь] Создан");
    }

    // Конструктор копирования: свой список слотов, но предметы остаются общими
    public Inventory(Inventory other) {
        this.items = new ArrayList<>(other.items);
        System.out.println("[Инвентарь] Скопирован (предметов: " + items.size() + ")");
    }

    // Заменяет содержимое слотов содержимым другого инвентаря
    public void copyFrom(Inventory other) {
        if (this == other) {
            return;
        }
        items.clear();
        items.addAll(other.items);
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

    // Индекс первого предмета, в названии которого есть подстрока, или -1
    public int findItem(String part) {
        for (int i = 0; i < items.size(); i++) {
            if (items.get(i).getName().indexOf(part) >= 0) {
                return i;
            }
        }
        return -1;
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
