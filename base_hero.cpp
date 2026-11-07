//
// ФАЙЛ base_hero.cpp
//

#include "base_hero.hpp"

#include <iostream>
#include <utility>

namespace game
{

BaseHero::BaseHero(std::string_view name, int health, int mana, int luck, int gold)
    : m_id{ NextId() }
    , m_name{ name }
    , m_health{ health }
    , m_mana{ mana }
    , m_luck{ luck }
    , m_gold{ gold }
{
    if (m_name.empty())
    {
        m_name = "Неизвестный Герой";
    }

    if (m_health <= 0)
    {
        m_health = 100;
    }

    if (m_mana < 0)
    {
        m_mana = 0;
    }

    if (m_luck < 0)
    {
        m_luck = 0;
    }

    if (m_gold < 0)
    {
        m_gold = 0;
    }

    std::cout << "[Герой] Создан: " << m_name << " (№" << m_id << ")\n";
}

// Копия — новый герой: свой номер, общая комната, свой инвентарь
BaseHero::BaseHero(const BaseHero& other)
    : m_id{ NextId() }
    , m_name{ other.m_name }
    , m_health{ other.m_health }
    , m_mana{ other.m_mana }
    , m_luck{ other.m_luck }
    , m_gold{ other.m_gold }
    , m_equipped{ other.m_equipped }
    , m_room{ other.m_room }
    , m_inventory{ other.m_inventory }
{
    std::cout << "[Герой] Копия: " << m_name << " (№" << m_id
              << ", оригинал №" << other.m_id << ")\n";
}

// Перемещение — тот же герой: номер сохраняется, прежний объект опустошается
BaseHero::BaseHero(BaseHero&& other) noexcept
    : m_id{ other.m_id }
    , m_name{ std::move(other.m_name) }
    , m_health{ other.m_health }
    , m_mana{ other.m_mana }
    , m_luck{ other.m_luck }
    , m_gold{ other.m_gold }
    , m_equipped{ std::move(other.m_equipped) }
    , m_room{ std::move(other.m_room) }
    , m_inventory{ std::move(other.m_inventory) }
{
    std::cout << "[Герой] Перемещён: " << m_name << " (№" << m_id << ")\n";
}

BaseHero& BaseHero::operator=(const BaseHero& other)
{
    if (this == &other)
    {
        std::cout << "[Герой] Самоприсваивание «" << m_name << "»: ничего не делаем\n";
        return *this;
    }

    // Номер остаётся своим: присваивание не создаёт нового героя
    m_name      = other.m_name;
    m_health    = other.m_health;
    m_mana      = other.m_mana;
    m_luck      = other.m_luck;
    m_gold      = other.m_gold;
    m_equipped  = other.m_equipped;
    m_room      = other.m_room;
    m_inventory = other.m_inventory;

    std::cout << "[Герой] Присвоено: №" << m_id << " теперь «" << m_name << "»\n";
    return *this;
}

BaseHero& BaseHero::operator=(BaseHero&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    m_name      = std::move(other.m_name);
    m_health    = other.m_health;
    m_mana      = other.m_mana;
    m_luck      = other.m_luck;
    m_gold      = other.m_gold;
    m_equipped  = std::move(other.m_equipped);
    m_room      = std::move(other.m_room);
    m_inventory = std::move(other.m_inventory);

    return *this;
}

BaseHero::~BaseHero()
{
    std::cout << "[Герой] Уничтожен: " << (m_name.empty() ? "<перемещён>" : m_name)
              << " (№" << m_id << ")\n";
}

std::string BaseHero::Header() const
{
    return m_name + " (№" + std::to_string(m_id) + ")";
}

std::string BaseHero::Describe() const
{
    std::string result = Header();
    result += " | Класс: ";
    result += GetClassName();
    result += " | ХП: " + std::to_string(m_health);
    result += " | Мана: " + std::to_string(m_mana);
    result += " | Удача: " + std::to_string(m_luck);
    result += " | Золото: " + std::to_string(m_gold);
    result += " | Предметов: " + std::to_string(m_inventory.GetSize());
    result += " | Комната: ";
    if (m_room)
    {
        result += m_room->GetName();
    }
    else
    {
        result += "нет";
    }
    return result;
}

void BaseHero::TakeDamage(int damage)
{
    if (damage < 0)
    {
        return;
    }

    m_health -= damage;
    if (m_health < 0)
    {
        m_health = 0;
    }

    std::cout << "[Герой] " << m_name << " получил " << damage
              << " урона. Осталось здоровья: " << m_health << "\n";
}

bool BaseHero::UseMana(int amount)
{
    if (amount <= 0)
    {
        return false;
    }

    if (m_mana < amount)
    {
        std::cout << "[Герой] " << m_name << ": Недостаточно маны! (Нужно: "
                  << amount << ", Есть: " << m_mana << ")\n";
        return false;
    }

    m_mana -= amount;
    std::cout << "[Герой] " << m_name << " потратил " << amount
              << " маны. Осталось маны: " << m_mana << "\n";
    return true;
}

bool BaseHero::SpendGold(int amount)
{
    if (amount <= 0)
    {
        return false;
    }

    if (m_gold < amount)
    {
        std::cout << "[Герой] " << m_name << ": Недостаточно золота! (Нужно: "
                  << amount << ", Есть: " << m_gold << ")\n";
        return false;
    }

    m_gold -= amount;
    std::cout << "[Герой] " << m_name << " потратил " << amount
              << " золота. Осталось золота: " << m_gold << "\n";
    return true;
}

void BaseHero::EarnGold(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    m_gold += amount;
    std::cout << "[Герой] " << m_name << " получил " << amount
              << " золота. Всего золота: " << m_gold << "\n";
}

bool BaseHero::PickUpItem(const std::shared_ptr<Item>& item)
{
    std::cout << "[Герой] " << m_name << " пытается подобрать предмет...\n";
    return m_inventory.AddItem(item);
}

std::shared_ptr<Item> BaseHero::DropItem(std::size_t index)
{
    std::cout << "[Герой] " << m_name << " выбрасывает предмет из слота " << index << "...\n";
    return m_inventory.RemoveItem(index);
}

bool BaseHero::EquipItem(std::size_t index)
{
    const std::shared_ptr<Item> item = m_inventory.GetItem(index);
    if (!item)
    {
        std::cout << "[Герой] " << m_name << ": в слоте " << index << " нет предмета!\n";
        return false;
    }

    if (item->GetType() != ItemType::eWeapon && item->GetType() != ItemType::eArmor)
    {
        std::cout << "[Герой] " << m_name << ": «" << item->GetName()
                  << "» нельзя экипировать!\n";
        return false;
    }

    m_equipped = item;
    std::cout << "[Герой] " << m_name << " экипировал: " << item->GetName() << "\n";
    return true;
}

void BaseHero::ShowEquipped() const
{
    if (const std::shared_ptr<Item> item = m_equipped.lock())
    {
        std::cout << "[Герой] " << m_name << ": экипировано «" << item->GetName() << "»\n";
    }
    else
    {
        std::cout << "[Герой] " << m_name << ": экипировки нет (предмет не выбран или уничтожен)\n";
    }
}

void BaseHero::EnterRoom(const std::shared_ptr<Room>& room)
{
    m_room = room;
    if (m_room)
    {
        // Передаём текущий объект комнате
        m_room->Welcome(*this);
    }
}

void BaseHero::RenameRoom(std::string_view name)
{
    if (m_room)
    {
        m_room->Rename(name);
    }
}

void BaseHero::Inspect() const
{
    std::cout << "========================================\n";
    std::cout << Describe() << "\n";
    m_inventory.PrintItems();
    std::cout << "========================================\n";
}

std::string BaseHero::GetFullTitle() const
{
    // Конкатенация
    return std::string{ GetClassName() } + " " + m_name;
}

std::string BaseHero::GetShortName() const
{
    // Поиск и выделение подстроки: имя до первого пробела
    const std::size_t pos = m_name.find(' ');
    if (pos == std::string::npos)
    {
        return m_name;
    }
    return m_name.substr(0, pos);
}

bool BaseHero::IsNamed(std::string_view name) const
{
    // Сравнение содержимого
    return m_name == name;
}

std::optional<std::size_t> BaseHero::FindItem(std::string_view part) const
{
    return m_inventory.FindItem(part);
}

} // namespace game
