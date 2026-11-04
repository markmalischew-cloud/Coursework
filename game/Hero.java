package game;

public class Hero {
    private String name;
    private int health;
    private int mana;
    private int gold;

    // Композиция: героя создаёт инвентарь сам и наружу его не отдаёт
    private final Inventory inventory;

    public Hero(String name, int health, int mana, int gold) {
        this.name = (name == null || name.isEmpty()) ? "Неизвестный Герой" : name;
        this.health = health <= 0 ? 100 : health;
        this.mana = Math.max(0, mana);
        this.gold = Math.max(0, gold);
        this.inventory = new Inventory();
        System.out.println("[Герой] Создан: " + this.name);
    }

    public void takeDamage(int damage) {
        if (damage < 0) {
            return;
        }
        health = Math.max(0, health - damage);
        System.out.println("[Герой] " + name + " получил " + damage
                + " урона. Осталось здоровья: " + health);
    }

    public boolean useMana(int amount) {
        if (amount <= 0) {
            return false;
        }
        if (mana < amount) {
            System.out.println("[Герой] " + name + ": Недостаточно маны! (Нужно: "
                    + amount + ", Есть: " + mana + ")");
            return false;
        }
        mana -= amount;
        System.out.println("[Герой] " + name + " потратил " + amount
                + " маны. Осталось маны: " + mana);
        return true;
    }

    public boolean spendGold(int amount) {
        if (amount <= 0) {
            return false;
        }
        if (gold < amount) {
            System.out.println("[Герой] " + name + ": Недостаточно золота! (Нужно: "
                    + amount + ", Есть: " + gold + ")");
            return false;
        }
        gold -= amount;
        System.out.println("[Герой] " + name + " потратил " + amount
                + " золота. Осталось золота: " + gold);
        return true;
    }

    public void earnGold(int amount) {
        if (amount <= 0) {
            return;
        }
        gold += amount;
        System.out.println("[Герой] " + name + " получил " + amount
                + " золота. Всего золота: " + gold);
    }

    public boolean pickUpItem(Item item) {
        System.out.println("[Герой] " + name + " пытается подобрать предмет...");
        return inventory.addItem(item);
    }

    public Item dropItem(int index) {
        System.out.println("[Герой] " + name + " выбрасывает предмет из слота " + index + "...");
        return inventory.removeItem(index);
    }

    public void inspect() {
        System.out.println("========================================");
        System.out.println(this);
        inventory.printItems();
        System.out.println("========================================");
    }

    public String getName() {
        return name;
    }

    public int getHealth() {
        return health;
    }

    public int getMana() {
        return mana;
    }

    public int getGold() {
        return gold;
    }

    public int getInventorySize() {
        return inventory.getSize();
    }

    @Override
    public String toString() {
        return "Герой: " + name + " | ХП: " + health + " | Мана: " + mana + " | Золото: " + gold;
    }
}
