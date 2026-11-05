package game;

public class Room {
    private String name;

    public Room(String name) {
        this.name = name;
        System.out.println("[Комната] Создана: " + name);
    }

    public void rename(String name) {
        this.name = name;
        System.out.println("[Комната] Переименована в \"" + name + "\"");
    }

    // Комната получает героя целиком и читает его данные
    public void welcome(BaseHero hero) {
        System.out.println("[Комната] \"" + name + "\": входит " + hero.getFullTitle());
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Комната " + name;
    }
}
