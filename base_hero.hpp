//
// ФАЙЛ base_hero.hpp
//
#pragma once

#include "inventory.hpp"
#include "room.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace game
{

// Абстрактный класс: общее состояние и поведение героев всех классов
class BaseHero
{
public:
    virtual ~BaseHero();

    // Чисто виртуальные: у каждого класса героя своя реализация
    [[nodiscard]] virtual std::string_view GetClassName() const = 0;
    [[nodiscard]] virtual int GetAttackDamage() const = 0;
    [[nodiscard]] virtual std::unique_ptr<BaseHero> Clone() const = 0;

    // Есть реализация; наследник может дополнить её или заменить
    [[nodiscard]] virtual std::string Describe() const;

    void TakeDamage(int damage);
    bool UseMana(int amount);

    bool SpendGold(int amount);
    void EarnGold(int amount);

    bool PickUpItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<Item> DropItem(std::size_t index);

    bool EquipItem(std::size_t index);
    void ShowEquipped() const;

    void EnterRoom(const std::shared_ptr<Room>& room);
    void RenameRoom(std::string_view name);

    void Inspect() const;

    // Работа со строками
    [[nodiscard]] std::string GetFullTitle() const;
    [[nodiscard]] std::string GetShortName() const;
    [[nodiscard]] bool IsNamed(std::string_view name) const;
    [[nodiscard]] std::optional<std::size_t> FindItem(std::string_view part) const;

    [[nodiscard]] int GetId() const { return m_id; }
    [[nodiscard]] std::string_view GetName() const { return m_name; }
    [[nodiscard]] int GetHealth() const { return m_health; }
    [[nodiscard]] int GetMana() const { return m_mana; }
    [[nodiscard]] int GetLuck() const { return m_luck; }
    [[nodiscard]] int GetGold() const { return m_gold; }
    [[nodiscard]] std::size_t GetInventorySize() const { return m_inventory.GetSize(); }

    // Сколько героев создано за всё время (одно значение на весь класс)
    [[nodiscard]] static int GetCreatedCount() { return m_lastId; }

protected:
    // Создать объект может только наследник
    BaseHero(std::string_view name, int health, int mana, int luck, int gold);

    // Копирование и перемещение недоступны снаружи: нет срезки.
    // Копируют только наследники и Clone()
    BaseHero(const BaseHero& other);
    BaseHero(BaseHero&& other) noexcept;
    BaseHero& operator=(const BaseHero& other);
    BaseHero& operator=(BaseHero&& other) noexcept;

    // Общая часть описания: нужна наследникам, остальному коду не нужна
    [[nodiscard]] std::string Header() const;

private:
    [[nodiscard]] static int NextId() { return ++m_lastId; }

    inline static int m_lastId{ 0 };

    int         m_id{ 0 };
    std::string m_name;
    int         m_health{ 100 };
    int         m_mana{ 50 };
    int         m_luck{ 5 };
    int         m_gold{ 0 };

    // Герой пользуется экипировкой, но не владеет ею
    std::weak_ptr<Item> m_equipped;

    // Комната общая: несколько героев могут быть в одной комнате (поверхностная копия)
    std::shared_ptr<Room> m_room;

    // Инвентарь свой у каждого героя (композиция, глубокая копия)
    Inventory m_inventory;
};

} // namespace game
