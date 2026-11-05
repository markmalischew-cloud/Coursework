package game;

public class Warrior extends BaseHero {
    private static final int BASE_DAMAGE = 20;
    private static final int WEAPON_BONUS_PERCENT = 15;

    public Warrior() {
        this("Безымянный воин", 0); // вызов другого конструктора этого же класса
        System.out.println("[Воин] Создан конструктором по умолчанию");
    }

    @SuppressWarnings("this-escape") // getName() у BaseHero final, вызов безопасен
    public Warrior(String name, int gold) {
        super(name, 150, 30, 5, gold); // сначала базовая часть
        System.out.println("[Воин] Создан: " + getName());
    }

    @SuppressWarnings("this-escape") // getName() у BaseHero final, вызов безопасен
    public Warrior(Warrior other) {
        super(other);
        System.out.println("[Воин] Копия: " + getName());
    }

    @Override
    public String getClassName() {
        return "Воин";
    }

    @Override
    public int getAttackDamage() {
        return BASE_DAMAGE * (100 + WEAPON_BONUS_PERCENT) / 100;
    }

    @Override
    public BaseHero copy() {
        return new Warrior(this);
    }

    // Дополняет описание базового класса
    @Override
    public String describe() {
        return super.describe() + " | Бонус классового оружия: +" + WEAPON_BONUS_PERCENT + "%";
    }
}
