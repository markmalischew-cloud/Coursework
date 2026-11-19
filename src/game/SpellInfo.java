package game;

public record SpellInfo(String name, int damage, int manaCost) {

    public static SpellInfo of(SpellElement element) {
        return switch (element) {
            case FIRE  -> new SpellInfo("Огонь",  40, 80);
            case WATER -> new SpellInfo("Вода",   25, 25);
            case EARTH -> new SpellInfo("Земля",  30, 40);
            case AIR   -> new SpellInfo("Воздух", 20, 20);
        };
    }
}
