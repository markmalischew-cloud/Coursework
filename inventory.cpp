//
// ФАЙЛ inventory.cpp
//

#include "inventory.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>

namespace game
{

Inventory::Inventory()
{
    std::cout << "[Инвентарь] Создан\n";
}

// Копирование: у копии свой набор слотов (сами предметы остаются общими)
Inventory::Inventory(const Inventory& other)
    : m_size{ other.m_size }
{
    std::copy_n(std::begin(other.m_items), other.m_size, std::begin(m_items));
    std::cout << "[Инвентарь] Скопирован (предметов: " << m_size << ")\n";
}

Inventory::Inventory(Inventory&& other) noexcept
    : m_size{ std::exchange(other.m_size, 0) }
{
    std::move(std::begin(other.m_items), std::begin(other.m_items) + m_size, std::begin(m_items));
    std::cout << "[Инвентарь] Перемещён (предметов: " << m_size << ")\n";
}

Inventory& Inventory::operator=(const Inventory& other)
{
    if (this == &other)
    {
        return *this;
    }

    Clear();
    std::copy_n(std::begin(other.m_items), other.m_size, std::begin(m_items));
    m_size = other.m_size;
    return *this;
}

Inventory& Inventory::operator=(Inventory&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    Clear();
    const std::size_t count = std::exchange(other.m_size, 0);
    std::move(std::begin(other.m_items), std::begin(other.m_items) + count, std::begin(m_items));
    m_size = count;
    return *this;
}

Inventory::~Inventory()
{
    std::cout << "[Инвентарь] Уничтожен\n";
}

void Inventory::Clear()
{
    for (std::size_t i = 0; i < m_size; ++i)
    {
        m_items[i].reset();
    }
    m_size = 0;
}

bool Inventory::AddItem(const std::shared_ptr<Item>& item)
{
    const auto first = std::begin(m_items);
    const auto last  = first + m_size;

    if (!item || m_size >= CAPACITY || std::find(first, last, item) != last)
    {
        std::cout << "[Инвентарь] Ошибка: не удалось добавить предмет!\n";
        return false;
    }

    m_items[m_size] = item;
    ++m_size;
    return true;
}

std::shared_ptr<Item> Inventory::RemoveItem(std::size_t index)
{
    if (index >= m_size)
    {
        std::cout << "[Инвентарь] Ошибка: неверный индекс для удаления!\n";
        return nullptr;
    }

    std::shared_ptr<Item> removed = std::move(m_items[index]);

    const auto first = std::begin(m_items);
    std::rotate(first + index, first + index + 1, first + m_size);
    --m_size;

    return removed;
}

std::shared_ptr<Item> Inventory::GetItem(std::size_t index) const
{
    if (index >= m_size)
    {
        return nullptr;
    }
    return m_items[index];
}

std::optional<std::size_t> Inventory::FindItem(std::string_view part) const
{
    for (std::size_t i = 0; i < m_size; ++i)
    {
        const std::string name{ m_items[i]->GetName() };
        if (name.find(part) != std::string::npos)
        {
            return i;
        }
    }
    return std::nullopt;
}

void Inventory::PrintItems() const
{
    std::cout << "--- Инвентарь (" << m_size << "/" << CAPACITY << ") ---\n";

    for (std::size_t i = 0; i < m_size; ++i)
    {
        std::cout << " Слот " << i << ": " << m_items[i]->GetName()
                  << " (владельцев: " << m_items[i].use_count() << ")\n";
    }
}

} // namespace game
