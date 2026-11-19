package game;

public class Monster implements Combatant {

    private final String name;
    private int health;
    private final int maxHealth;
    private final int attackDamage;
    private MonsterTactic tactic; // объект поведения, можно заменить во время работы

    public Monster(String name, int health, int attackDamage, MonsterTactic tactic) {
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("имя монстра не может быть пустым");
        }
        if (health <= 0) {
            throw new IllegalArgumentException("здоровье монстра должно быть больше нуля");
        }
        if (attackDamage < 0) {
            throw new IllegalArgumentException("урон монстра не может быть отрицательным");
        }
        if (tactic == null) {
            throw new IllegalArgumentException("у монстра должна быть тактика");
        }
        this.name = name;
        this.health = health;
        this.maxHealth = health;
        this.attackDamage = attackDamage;
        this.tactic = tactic;
        System.out.println("[Монстр] Создан: " + name + " (тактика: " + tactic.getName() + ")");
    }

    // Контракт Combatant
    @Override public String getName()      { return name; }
    @Override public int getAttackDamage() { return attackDamage; }
    @Override public boolean isAlive()     { return health > 0; }

    @Override
    public void takeDamage(int damage) {
        if (damage < 0) {
            throw new IllegalArgumentException("урон не может быть отрицательным");
        }
        health = Math.max(0, health - damage);
        System.out.println("[Монстр] " + name + " получил " + damage
                + " урона. Осталось здоровья: " + health);
    }

    // Динамическое конфигурирование: тактику можно заменить во время работы
    public void setTactic(MonsterTactic tactic) {
        if (tactic == null) {
            throw new IllegalArgumentException("у монстра должна быть тактика");
        }
        this.tactic = tactic;
        System.out.println("[Монстр] " + name + " меняет тактику на: " + tactic.getName());
    }

    // Решение принимает объект поведения, а не сам монстр
    public MonsterAction chooseAction() { return tactic.decide(getHealthPercent()); }

    public String getTacticName() { return tactic.getName(); }
    public int getHealth()        { return health; }
    public int getHealthPercent() { return health * 100 / maxHealth; }
}
