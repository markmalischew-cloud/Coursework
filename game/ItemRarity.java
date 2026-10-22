package game;

public enum ItemRarity {
    COMMON(1, "обычный"),
    UNCOMMON(2, "необычный"),
    RARE(3, "редкий"),
    EPIC(4, "эпический"),
    LEGENDARY(5, "легендарный");

    private final int level;
    private final String title;

    ItemRarity(int level, String title) {
        this.level = level;
        this.title = title;
    }

    public int getLevel() {
        return level;
    }

    @Override
    public String toString() {
        return title;
    }
}
