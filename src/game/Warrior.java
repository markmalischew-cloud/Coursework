package game;

// Множественное наследование: абстрактный класс BaseHero и интерфейс SpellCaster
public class Warrior extends BaseHero implements SpellCaster {

    private static final int BASE_DAMAGE          = 20;
    private static final int WEAPON_BONUS_PERCENT = 15;
    private static final int SPELL_BONUS_PERCENT  = 0;

    public Warrior() { this("Безымянный воин", 0); }

    public Warrior(String name, int gold) {
        super(name, 150, 30, 5, gold);
        System.out.println("[Воин] Создан: " + name);
    }

    // Скрывает BaseHero.getKind(): раннее связывание, НЕ переопределение
    public static String getKind() { return "воин"; }

    @Override public String getClassName() { return "Воин"; }

    @Override
    public int getAttackDamage() {
        return BASE_DAMAGE * (100 + WEAPON_BONUS_PERCENT) / 100;
    }

    @Override public BaseHero clone() { return new Warrior(getName(), getGold()); }

    // Дополняет описание базового класса
    @Override
    public String describe() {
        return super.describe() + " | Бонус классового оружия: +"
                + WEAPON_BONUS_PERCENT + "%";
    }

    // Контракт SpellCaster: у воина нет бонуса к заклинаниям
    @Override public int castSpell(SpellElement element) {
        return performSpell(element, SPELL_BONUS_PERCENT);
    }
}
