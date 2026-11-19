//
// ФАЙЛ base_hero.hpp
//
#pragma once

#include "i_combatant.hpp"
#include "inventory.hpp"
#include "room.hpp"
#include "spell.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace game
{

// Абстрактный класс героя. Реализует контракт ICombatant:
// GetAttackDamage() остаётся чисто виртуальным и приходит из интерфейса
class BaseHero : public ICombatant
{
public:
    ~BaseHero() noexcept override;

    [[nodiscard]] virtual std::string_view GetClassName() const = 0;
    [[nodiscard]] virtual std::unique_ptr<BaseHero> Clone() const = 0;

    // Есть реализация; наследник может дополнить её или заменить
    [[nodiscard]] virtual std::string Describe() const;

    // Раннее связывание: невиртуальный метод, версия выбирается по типу ссылки
    [[nodiscard]] std::string_view GetKind() const { return "герой"; }

    // Контракт ICombatant
    [[nodiscard]] std::string_view GetName() const override { return m_name; }
    void TakeDamage(int damage) override;
    [[nodiscard]] bool IsAlive() const override { return m_health > 0; }

    // Следующие методы бросают исключение, если правило нарушено,
    // и при этом не меняют героя
    void UseMana(int amount);
    void SpendGold(int amount);
    void EarnGold(int amount);

    void PickUpItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<Item> DropItem(std::size_t index);

    void EquipItem(std::size_t index);
    void ShowEquipped() const;

    void EnterCombat();
    void LeaveCombat();
    [[nodiscard]] bool IsInCombat() const { return m_inCombat; }

    void EnterRoom(const std::shared_ptr<Room>& room);
    void RenameRoom(std::string_view name);

    void Inspect() const;

    // Работа со строками
    [[nodiscard]] std::string GetFullTitle() const;
    [[nodiscard]] std::string GetShortName() const;
    [[nodiscard]] bool IsNamed(std::string_view name) const;
    [[nodiscard]] std::optional<std::size_t> FindItem(std::string_view part) const;

    [[nodiscard]] int GetId() const { return m_id; }
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

    // Общая часть заклинания: тратит ману (может бросить исключение)
    // и возвращает урон с учётом бонуса класса
    [[nodiscard]] int PerformSpell(SpellElement element, int bonusPercent);

private:
    [[nodiscard]] static int NextId() { return ++m_lastId; }

    inline static int m_lastId{ 0 };

    int         m_id{ 0 };
    std::string m_name;
    int         m_health{ 100 };
    int         m_mana{ 50 };
    int         m_luck{ 5 };
    int         m_gold{ 0 };
    bool        m_inCombat{ false };

    // Герой пользуется экипировкой, но не владеет ею
    std::weak_ptr<Item> m_equipped;

    // Комната общая: несколько героев могут быть в одной комнате (поверхностная копия)
    std::shared_ptr<Room> m_room;

    // Инвентарь свой у каждого героя (композиция, глубокая копия)
    Inventory m_inventory;
};

} // namespace game
