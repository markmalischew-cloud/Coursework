package game;

public enum MonsterAction {
    ATTACK("атаковать"),
    FLEE("бежать"),
    BEG_FOR_MERCY("просить пощады");

    private final String title;

    MonsterAction(String title) { this.title = title; }

    public String getTitle() { return title; }
}
