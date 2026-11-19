package game;

// Ресурс, который должен освобождаться при любом исходе.
// В C++ то же делает деструктор (RAII), в Java — try-with-resources.
public class BattleLog implements AutoCloseable {

    private final StringBuilder buffer = new StringBuilder();

    public BattleLog() {
        System.out.println("[Журнал] Открыт");
    }

    public void write(String line) {
        buffer.append(line).append('\n');
    }

    @Override
    public void close() {
        System.out.println("[Журнал] Закрыт, записано строк: "
                + buffer.toString().lines().count());
    }
}
