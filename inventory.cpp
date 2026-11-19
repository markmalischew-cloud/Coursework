//
// ФАЙЛ inventory.cpp
//

#include "inventory.hpp"

#include "game_error.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
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

Inventory::~Inventory() noexcept
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

void Inventory::AddItem(const std::shared_ptr<Item>& item)
{
    // Все проверки идут до изменения инвентаря: гарантия "всё или ничего"
    if (!item)
    {
        throw std::invalid_argument{ "предмет не задан" };
    }

    const auto first = std::begin(m_items);
    const auto last  = first + m_size;

    if (std::find(first, last, item) != last)
    {
        throw std::invalid_argument{ "этот предмет уже лежит в инвентаре" };
    }

    if (m_size >= CAPACITY)
    {
        throw InventoryFullError{ CAPACITY };
    }

    m_items[m_size] = item;
    ++m_size;
}

std::shared_ptr<Item> Inventory::RemoveItem(std::size_t index)
{
    if (index >= m_size)
    {
        throw std::out_of_range{ "неверный индекс слота: " + std::to_string(index) };
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
        throw std::out_of_range{ "в слоте " + std::to_string(index) + " нет предмета" };
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
