package game;

public final class Combat {

    private Combat() {}

    // Работает только с контрактом: не знает, герой перед ним или монстр
    public static void attack(Combatant attacker, Combatant target) {
        if (!attacker.isAlive()) {
            throw new IllegalStateException("мёртвый не может атаковать");
        }
        int damage = attacker.getAttackDamage();
        System.out.println(attacker.getName() + " атакует " + target.getName()
                + " (урон " + damage + ")");
        target.takeDamage(damage);
    }

    // Проверка типа во время выполнения через instanceof.
    // Java 16+: pattern matching — не нужно вручную кастовать.
    // Проверка уместна на границе: "умеет ли объект это вообще".
    public static void castSpellAt(Combatant who, Combatant target, SpellElement element) {
        if (who instanceof SpellCaster caster) {
            int damage = caster.castSpell(element);
            target.takeDamage(damage);
        } else {
            System.out.println(who.getName() + " не умеет колдовать");
        }
    }
}
