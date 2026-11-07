package game;

public class Mage extends BaseHero {
    private static final int BASE_DAMAGE = 8;
    private static final int SPELL_BONUS_PERCENT = 20;

    public Mage() {
        this("Безымянный маг", 0);
        System.out.println("[Маг] Создан конструктором по умолчанию");
    }

    @SuppressWarnings("this-escape") // getName() у BaseHero final, вызов безопасен
    public Mage(String name, int gold) {
        super(name, 80, 120, 5, gold);
        System.out.println("[Маг] Создан: " + getName());
    }

    @SuppressWarnings("this-escape") // getName() у BaseHero final, вызов безопасен
    public Mage(Mage other) {
        super(other);
        System.out.println("[Маг] Копия: " + getName());
    }

    @Override
    public String getClassName() {
        return "Маг";
    }

    @Override
    public int getAttackDamage() {
        return BASE_DAMAGE;
    }

    @Override
    public BaseHero copy() {
        return new Mage(this);
    }

    // Полностью заменяет описание базового класса; header() доступен наследнику
    @Override
    public String describe() {
        return "Маг " + header() + " | Мана: " + getMana()
                + " | Бонус заклинаний: +" + SPELL_BONUS_PERCENT + "%";
    }
}
