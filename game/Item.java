package game;

public class Item {
    private static final String DEFAULT_NAME = "Неизвестный предмет";

    private final String name;
    private final ItemType type;
    private final ItemRarity rarity;
    private final int price;

    public Item(String name, ItemType type, ItemRarity rarity, int price) {
        this.name = isValidName(name) ? name : DEFAULT_NAME;
        this.type = type != null ? type : ItemType.TREASURE;
        this.rarity = rarity != null ? rarity : ItemRarity.COMMON;
        this.price = Math.max(0, price);
        System.out.println("[Предмет] Создан: " + this.name);
    }

    private static boolean isValidName(String name) {
        return name != null
                && !name.isEmpty()
                && name.chars().allMatch(ch -> Character.isLetter(ch) || ch == ' ');
    }

    public String getName() {
        return name;
    }

    public ItemType getType() {
        return type;
    }

    public ItemRarity getRarity() {
        return rarity;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return name + " [" + type + ", " + rarity + ", " + price + " зол.]";
    }
}
