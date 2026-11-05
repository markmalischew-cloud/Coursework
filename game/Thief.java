package game;

// final: от вора никто не наследуется, продолжать иерархию незачем
public final class Thief extends BaseHero {
    // Вор не получает прибавок к урону: его сила в удаче
    private static final int BASE_DAMAGE = 12;

    public Thief() {
        this("Безымянный вор", 0);
        System.out.println("[Вор] Создан конструктором по умолчанию");
    }

    public Thief(String name, int gold) {
        super(name, 110, 30, 25, gold);
        System.out.println("[Вор] Создан: " + getName());
    }

    public Thief(Thief other) {
        super(other);
        System.out.println("[Вор] Копия: " + getName());
    }

    @Override
    public String getClassName() {
        return "Вор";
    }

    @Override
    public int getAttackDamage() {
        return BASE_DAMAGE;
    }

    @Override
    public BaseHero copy() {
        return new Thief(this);
    }
}
