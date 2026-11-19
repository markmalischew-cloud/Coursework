package game;

// final: от вора никто не наследуется, продолжать иерархию незачем
public final class Thief extends BaseHero implements SpellCaster {

    private static final int BASE_DAMAGE         = 12;
    private static final int SPELL_BONUS_PERCENT = 0;

    public Thief() { this("Безымянный вор", 0); }

    public Thief(String name, int gold) {
        super(name, 110, 30, 25, gold);
        System.out.println("[Вор] Создан: " + name);
    }

    // Скрывает BaseHero.getKind(): раннее связывание
    public static String getKind() { return "вор"; }

    @Override public String getClassName() { return "Вор"; }
    @Override public int getAttackDamage() { return BASE_DAMAGE; }
    @Override public BaseHero clone() { return new Thief(getName(), getGold()); }

    // У вора нет бонуса к заклинаниям: его сила в удаче
    @Override public int castSpell(SpellElement element) {
        return performSpell(element, SPELL_BONUS_PERCENT);
    }
}
