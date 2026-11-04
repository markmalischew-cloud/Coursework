package game;

public class AdventureLog implements AutoCloseable {
    private final String title;
    private int entries;
    private boolean closed;

    public AdventureLog(String title) {
        this.title = title;
        System.out.println("[+] журнал открыт: " + title);
    }

    public void write(String line) {
        if (closed) {
            throw new IllegalStateException("Журнал уже закрыт: " + title);
        }
        entries++;
        System.out.println("    запись " + entries + ": " + line);
    }

    public boolean isClosed() {
        return closed;
    }

    @Override
    public void close() {
        closed = true;
        System.out.println("[-] журнал закрыт: " + title + " (записей: " + entries + ")");
    }
}
