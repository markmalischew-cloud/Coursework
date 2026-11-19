package game;

// Множественное наследование: BaseHero + SpellCaster
public class Mage extends BaseHero implements SpellCaster {

    private static final int BASE_DAMAGE         = 8;
    private static final int SPELL_BONUS_PERCENT = 20;

    public Mage() { this("Безымянный маг", 0); }

    public Mage(String name, int gold) {
        super(name, 80, 120, 5, gold);
        System.out.println("[Маг] Создан: " + name);
    }

    // Скрывает BaseHero.getKind(): раннее связывание
    public static String getKind() { return "маг"; }

    @Override public String getClassName() { return "Маг"; }
    @Override public int getAttackDamage() { return BASE_DAMAGE; }
    @Override public BaseHero clone() { return new Mage(getName(), getGold()); }

    // Полностью заменяет описание базового класса
    @Override
    public String describe() {
        return "Маг " + header()
                + " | Мана: " + getMana()
                + " | Бонус заклинаний: +" + SPELL_BONUS_PERCENT + "%";
    }

    @Override public int castSpell(SpellElement element) {
        return performSpell(element, SPELL_BONUS_PERCENT);
    }
}
