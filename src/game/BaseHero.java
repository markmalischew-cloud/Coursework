package game;

import java.util.Optional;

// Абстрактный класс героя. Реализует контракт Combatant:
// getAttackDamage() остаётся абстрактным и приходит из интерфейса.
// Реализует Comparable<BaseHero> — упорядочивание героев по имени.
public abstract class BaseHero implements Combatant, Comparable<BaseHero> {

    private static int lastId = 0;

    private final int id;
    private final String name;
    private int health;
    private int mana;
    private int luck;
    private int gold;
    private boolean inCombat;
    private Item equipped;       // герой пользуется, но не владеет
    private Room room;           // комната общая
    private final Inventory inventory = new Inventory(); // инвентарь свой

    // Создать объект может только наследник
    protected BaseHero(String name, int health, int mana, int luck, int gold) {
        // Раньше неверные значения молча заменялись, теперь это исключение
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("имя героя не может быть пустым");
        }
        if (health <= 0) {
            throw new IllegalArgumentException("здоровье героя должно быть больше нуля");
        }
        if (mana < 0 || luck < 0 || gold < 0) {
            throw new IllegalArgumentException("мана, удача и золото не могут быть отрицательными");
        }

        this.id = ++lastId; // номер выдаётся только когда герой точно создан
        this.name = name;
        this.health = health;
        this.mana = mana;
        this.luck = luck;
        this.gold = gold;

        System.out.println("[Герой] Создан: " + name + " (№" + id + ")");
    }

    // ----- абстрактные методы наследников -----

    public abstract String getClassName();
    public abstract BaseHero clone();

    // ----- описание -----

    public String describe() {
        StringBuilder sb = new StringBuilder(header());
        sb.append(" | Класс: ").append(getClassName());
        sb.append(" | ХП: ").append(health);
        sb.append(" | Мана: ").append(mana);
        sb.append(" | Удача: ").append(luck);
        sb.append(" | Золото: ").append(gold);
        sb.append(" | Предметов: ").append(inventory.size());
        sb.append(" | Комната: ").append(room == null ? "нет" : room.getName());
        return sb.toString();
    }

    public static String getKind() {
        return "герой";
    }

    protected String header() {
        return name + " (№" + id + ")";
    }

    // ----- контракт Combatant -----

    @Override public String getName()  { return name; }
    @Override public boolean isAlive() { return health > 0; }

    @Override
    public void takeDamage(int damage) {
        if (damage < 0) {
            throw new IllegalArgumentException("урон не может быть отрицательным");
        }
        health -= damage;
        if (health < 0) health = 0;
        System.out.println("[Герой] " + name + " получил " + damage
                + " урона. Осталось здоровья: " + health);
    }

    // ----- ресурсы: проверки до изменения — строгая гарантия -----

    public void useMana(int amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("расход маны должен быть больше нуля");
        }
        if (mana < amount) {
            throw new NotEnoughManaException(amount, mana);
        }
        mana -= amount;
        System.out.println("[Герой] " + name + " потратил " + amount
                + " маны. Осталось маны: " + mana);
    }

    public void spendGold(int amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("сумма трат должна быть больше нуля");
        }
        if (gold < amount) {
            throw new NotEnoughGoldException(amount, gold);
        }
        gold -= amount;
        System.out.println("[Герой] " + name + " потратил " + amount
                + " золота. Осталось золота: " + gold);
    }

    public void earnGold(int amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("доход должен быть больше нуля");
        }
        gold += amount;
        System.out.println("[Герой] " + name + " получил " + amount
                + " золота. Всего золота: " + gold);
    }

    // ----- инвентарь -----

    public void pickUpItem(Item item) {
        System.out.println("[Герой] " + name + " пытается подобрать предмет...");
        inventory.addItem(item);
    }

    public Item dropItem(int index) {
        System.out.println("[Герой] " + name + " выбрасывает предмет из слота " + index + "...");
        return inventory.removeItem(index);
    }

    public void equipItem(int index) {
        // Правило 3: во время боя экипировку менять нельзя
        if (inCombat) {
            throw new ForbiddenInCombatException("сменить экипировку");
        }
        Item item = inventory.getItem(index);
        if (item.getType() != Item.Type.WEAPON && item.getType() != Item.Type.ARMOR) {
            throw new IllegalArgumentException("предмет '" + item.getName() + "' нельзя экипировать");
        }
        equipped = item;
        System.out.println("[Герой] " + name + " экипировал: " + item.getName());
    }

    public void showEquipped() {
        if (equipped != null) {
            System.out.println("[Герой] " + name + ": экипировано " + equipped.getName());
        } else {
            System.out.println("[Герой] " + name + ": экипировки нет");
        }
    }

    // ----- бой и комната -----

    public void enterCombat() {
        inCombat = true;
        System.out.println("[Герой] " + name + " вступает в бой");
    }

    public void leaveCombat() {
        inCombat = false;
        System.out.println("[Герой] " + name + " выходит из боя");
    }

    public boolean isInCombat() { return inCombat; }

    public void enterRoom(Room room) {
        this.room = room;
        if (room != null) room.welcome(this);
    }

    public void renameRoom(String newName) {
        if (room != null) room.rename(newName);
    }

    public void inspect() {
        System.out.println("========================================");
        System.out.println(describe());
        inventory.printItems();
        System.out.println("========================================");
    }

    // ----- строковые операции -----

    public String getFullTitle() { return getClassName() + " " + name; }

    public String getShortName() {
        int pos = name.indexOf(' ');
        return pos < 0 ? name : name.substring(0, pos);
    }

    public boolean isNamed(String other) { return name.equals(other); }

    public Optional<Integer> findItem(String part) { return inventory.findItem(part); }

    // ----- общая часть заклинания -----

    // Тратит ману (может бросить исключение) и возвращает урон с учётом бонуса класса
    protected int performSpell(SpellElement element, int bonusPercent) {
        SpellInfo spell = SpellInfo.of(element);
        useMana(spell.manaCost()); // сначала мана: при нехватке исключение до любых изменений
        int damage = spell.damage() * (100 + bonusPercent) / 100;
        System.out.println("[Герой] " + name + " колдует " + spell.name()
                + ": урон " + damage);
        return damage;
    }

    // ----- геттеры -----

    public int getId()            { return id; }
    public int getHealth()        { return health; }
    public int getMana()          { return mana; }
    public int getLuck()          { return luck; }
    public int getGold()          { return gold; }
    public int getInventorySize() { return inventory.size(); }
    public static int getCreatedCount() { return lastId; }

    // ----- Comparable<BaseHero>: упорядочивание по имени -----

    @Override
    public int compareTo(BaseHero other) {
        return this.name.compareTo(other.name);
    }
}
