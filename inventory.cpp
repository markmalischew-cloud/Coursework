//
// ФАЙЛ inventory.cpp
//

#include "inventory.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

namespace game
{

Inventory::Inventory()
{
    std::cout << "[Инвентарь] Создан\n";
}

Inventory::~Inventory()
{
    std::cout << "[Инвентарь] Уничтожен\n";
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
