package game;

public enum ItemType {
    WEAPON("оружие"),
    ARMOR("броня"),
    CONSUMABLE("расходник"),
    TREASURE("сокровище");

    private final String title;

    ItemType(String title) {
        this.title = title;
    }

    @Override
    public String toString() {
        return title;
    }
}
