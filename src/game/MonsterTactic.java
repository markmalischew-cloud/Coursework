package game;

// Объект поведения: решает, что монстр делает в свой ход
public interface MonsterTactic {
    MonsterAction decide(int healthPercent);
    String getName();
}
