package game;

public class Item {

    public enum Type { WEAPON, ARMOR, CONSUMABLE, TREASURE }

    public enum Rarity {
        COMMON(1), UNCOMMON(2), RARE(3), EPIC(4), LEGENDARY(5);

        private final int value;
        Rarity(int v) { this.value = v; }
        public int getValue() { return value; }
    }

    private final String name;
    private final Type type;
    private final Rarity rarity;
    private final int price;

    public Item(String name, Type type, Rarity rarity, int price) {
        // Проверки идут до присваивания: объект либо создан корректно, либо исключение
        if (name == null || name.isEmpty()
                || !name.chars().allMatch(ch -> Character.isLetter(ch) || ch == ' ')) {
            throw new IllegalArgumentException("некорректное название предмета");
        }
        if (type == null) {
            throw new IllegalArgumentException("тип предмета не задан");
        }
        if (rarity == null) {
            throw new IllegalArgumentException("редкость предмета не задана");
        }
        if (rarity.getValue() < 1 || rarity.getValue() > 5) {
            throw new IllegalArgumentException("редкость предмета должна быть от 1 до 5");
        }
        if (price < 0) {
            throw new IllegalArgumentException("цена предмета не может быть отрицательной");
        }

        this.name = name;
        this.type = type;
        this.rarity = rarity;
        this.price = price;

        System.out.println("[Предмет] Создан: " + name);
    }

    public String getName()   { return name; }
    public Type   getType()   { return type; }
    public Rarity getRarity() { return rarity; }
    public int    getPrice()  { return price; }
}
