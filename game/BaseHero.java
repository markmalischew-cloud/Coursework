package game;

import java.util.Objects;

// Абстрактный класс: общее состояние и поведение героев всех классов
public abstract class BaseHero {
    // Одно значение на весь класс: сколько героев создано
    private static int lastId = 0;

    private final int id;
    private String name;
    private int health;
    private int mana;
    private int luck;
    private int gold;

    private Item equipped;

    // Комната общая: копия героя делит её с оригиналом (поверхностная копия)
    private Room room;

    // Инвентарь свой у каждого героя (композиция, глубокая копия)
    private final Inventory inventory;

    // Создать героя может только наследник
    protected BaseHero(String name, int health, int mana, int luck, int gold) {
        this.id = nextId();
        this.name = (name == null || name.isEmpty()) ? "Неизвестный Герой" : name;
        this.health = health <= 0 ? 100 : health;
        this.mana = Math.max(0, mana);
        this.luck = Math.max(0, luck);
        this.gold = Math.max(0, gold);
        this.inventory = new Inventory();
        System.out.println("[Герой] Создан: " + this.name + " (№" + id + ")");
    }

    // Копия: новый герой с новым номером, общая комната, свой инвентарь
    protected BaseHero(BaseHero other) {
        this.id = nextId();
        this.name = other.name;
        this.health = other.health;
        this.mana = other.mana;
        this.luck = other.luck;
        this.gold = other.gold;
        this.equipped = other.equipped;
        this.room = other.room;
        this.inventory = new Inventory(other.inventory);
        System.out.println("[Герой] Копия: " + name + " (№" + id + ", оригинал №" + other.id + ")");
    }

    // Абстрактные методы: у каждого класса героя своя реализация
    public abstract String getClassName();

    public abstract int getAttackDamage();

    public abstract BaseHero copy();

    // Есть реализация; наследник может дополнить её или заменить
    public String describe() {
        return header()
                + " | Класс: " + getClassName()
                + " | ХП: " + health
                + " | Мана: " + mana
                + " | Удача: " + luck
                + " | Золото: " + gold
                + " | Предметов: " + inventory.getSize()
                + " | Комната: " + (room == null ? "нет" : room.getName());
    }

    // Общая часть описания: нужна наследникам, остальному коду не нужна
    protected String header() {
        return name + " (№" + id + ")";
    }

    // В Java нет оператора присваивания, поэтому состояние копирует метод.
    // Он возвращает this, чтобы можно было строить цепочку
    public BaseHero copyStateFrom(BaseHero other) {
        if (this == other) {
            System.out.println("[Герой] Самоприсваивание " + name + ": ничего не делаем");
            return this;
        }
        if (getClass() != other.getClass()) {
            throw new IllegalArgumentException("Можно копировать состояние только героя того же класса");
        }

        // Номер остаётся своим: это не новый герой
        name = other.name;
        health = other.health;
        mana = other.mana;
        luck = other.luck;
        gold = other.gold;
        equipped = other.equipped;
        room = other.room;
        inventory.copyFrom(other.inventory);

        System.out.println("[Герой] Присвоено: №" + id + " теперь \"" + name + "\"");
        return this;
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
        Item dropped = inventory.removeItem(index);
        if (dropped != null && dropped == equipped) {
            equipped = null;
        }
        return dropped;
    }

    public boolean equipItem(int index) {
        Item item = inventory.getItem(index);
        if (item == null) {
            System.out.println("[Герой] " + name + ": в слоте " + index + " нет предмета!");
            return false;
        }
        if (item.getType() != ItemType.WEAPON && item.getType() != ItemType.ARMOR) {
            System.out.println("[Герой] " + name + ": \"" + item.getName() + "\" нельзя экипировать!");
            return false;
        }
        equipped = item;
        System.out.println("[Герой] " + name + " экипировал: " + item.getName());
        return true;
    }

    public void showEquipped() {
        if (equipped != null) {
            System.out.println("[Герой] " + name + ": экипировано \"" + equipped.getName() + "\"");
        } else {
            System.out.println("[Герой] " + name + ": экипировки нет");
        }
    }

    public void enterRoom(Room room) {
        this.room = room;
        if (room != null) {
            // Передаём текущий объект комнате
            room.welcome(this);
        }
    }

    public void renameRoom(String newName) {
        if (room != null) {
            room.rename(newName);
        }
    }

    public void inspect() {
        System.out.println("========================================");
        System.out.println(describe());
        inventory.printItems();
        System.out.println("========================================");
    }

    // Работа со строками
    public String getFullTitle() {
        return getClassName() + " " + name;
    }

    public String getShortName() {
        int pos = name.indexOf(' ');
        if (pos < 0) {
            return name;
        }
        return name.substring(0, pos);
    }

    public boolean isNamed(String otherName) {
        return name.equals(otherName);
    }

    public int findItem(String part) {
        return inventory.findItem(part);
    }

    public int getId() {
        return id;
    }

    public final String getName() {
        return name;
    }

    public int getHealth() {
        return health;
    }

    public int getMana() {
        return mana;
    }

    public int getLuck() {
        return luck;
    }

    public int getGold() {
        return gold;
    }

    public int getInventorySize() {
        return inventory.getSize();
    }

    private static int nextId() {
        return ++lastId;
    }

    public static int getCreatedCount() {
        return lastId;
    }

    // Герои равны, если совпадают класс и имя
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        BaseHero other = (BaseHero) o;
        return name.equals(other.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(getClassName(), name);
    }

    @Override
    public String toString() {
        return describe();
    }
}
