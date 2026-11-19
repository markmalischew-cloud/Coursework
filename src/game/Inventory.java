package game;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Inventory {

    public static final int CAPACITY = 20;
    private final List<Item> items = new ArrayList<>();

    public Inventory() {
        System.out.println("[Инвентарь] Создан");
    }

    // Бросает исключение, если предмет добавить нельзя; инвентарь при этом не меняется
    public void addItem(Item item) {
        // Все проверки до изменения: гарантия "всё или ничего"
        if (item == null) {
            throw new IllegalArgumentException("предмет не задан");
        }
        if (items.contains(item)) {
            throw new IllegalArgumentException("этот предмет уже лежит в инвентаре");
        }
        if (items.size() >= CAPACITY) {
            throw new InventoryFullException(CAPACITY);
        }
        items.add(item);
    }

    public Item removeItem(int index) {
        if (index < 0 || index >= items.size()) {
            throw new IndexOutOfBoundsException("неверный индекс слота: " + index);
        }
        return items.remove(index);
    }

    public Item getItem(int index) {
        if (index < 0 || index >= items.size()) {
            throw new IndexOutOfBoundsException("в слоте " + index + " нет предмета");
        }
        return items.get(index);
    }

    // Поиск предмета, в названии которого встречается подстрока
    public Optional<Integer> findItem(String part) {
        for (int i = 0; i < items.size(); ++i) {
            if (items.get(i).getName().contains(part)) {
                return Optional.of(i);
            }
        }
        return Optional.empty();
    }

    public void printItems() {
        System.out.println("--- Инвентарь (" + items.size() + "/" + CAPACITY + ") ---");
        for (int i = 0; i < items.size(); ++i) {
            System.out.println(" Слот " + i + ": " + items.get(i).getName());
        }
    }

    public int size() { return items.size(); }
}
