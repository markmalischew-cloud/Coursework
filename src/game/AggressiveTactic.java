package game;

// Всегда атакует
public final class AggressiveTactic implements MonsterTactic {
    @Override public MonsterAction decide(int healthPercent) { return MonsterAction.ATTACK; }
    @Override public String getName() { return "агрессивная"; }
}
