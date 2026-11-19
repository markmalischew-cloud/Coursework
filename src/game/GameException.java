package game;

// Нарушение правила игры во время работы программы.
// Что с ним делать, решает вызывающий код
public class GameException extends RuntimeException {
    public GameException(String message) { super(message); }
}

// Правило 5: заклинание доступно, только если хватает маны
class NotEnoughManaException extends GameException {
    public NotEnoughManaException(int required, int available) {
        super("не хватает маны: нужно " + required + ", есть " + available);
    }
}

class NotEnoughGoldException extends GameException {
    public NotEnoughGoldException(int required, int available) {
        super("не хватает золота: нужно " + required + ", есть " + available);
    }
}

class InventoryFullException extends GameException {
    public InventoryFullException(int capacity) {
        super("инвентарь полон, слотов: " + capacity);
    }
}

// Правило 3: во время боя нельзя менять экипировку
class ForbiddenInCombatException extends GameException {
    public ForbiddenInCombatException(String action) {
        super("во время боя нельзя: " + action);
    }
}
