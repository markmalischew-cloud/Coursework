package game;

// Контракт: умеет колдовать заклинания стихий
public interface SpellCaster {
    // Колдует заклинание и возвращает нанесённый урон.
    // Бросает NotEnoughManaException, если маны не хватает
    int castSpell(SpellElement element);
}
