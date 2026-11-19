package game;

// Просит пощады, когда здоровья меньше порога
public final class BeggingTactic implements MonsterTactic {

    private final int thresholdPercent;

    public BeggingTactic(int thresholdPercent) {
        if (thresholdPercent < 0 || thresholdPercent > 100) {
            throw new IllegalArgumentException("порог здоровья должен быть от 0 до 100 процентов");
        }
        this.thresholdPercent = thresholdPercent;
    }

    @Override
    public MonsterAction decide(int healthPercent) {
        return healthPercent < thresholdPercent ? MonsterAction.BEG_FOR_MERCY : MonsterAction.ATTACK;
    }

    @Override public String getName() { return "просящая пощады"; }
}
