package game;

// Контракт: тот, кто может участвовать в бою (герой или монстр)
public interface Combatant {
    String getName();
    int getAttackDamage();
    void takeDamage(int damage);
    boolean isAlive();
}
