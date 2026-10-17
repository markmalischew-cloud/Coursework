//
// ФАЙЛ inventory.cpp
//

#include "inventory.hpp"
#include <iostream>
#include <algorithm>

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

bool Inventory::AddItem(Item* item)
{
    const auto end = m_items.begin() + m_size;

    if (item == nullptr
        || m_size >= m_items.size()
        || std::find(m_items.begin(), end, item) != end)
    {
        std::cout << "[Инвентарь] Ошибка: не удалось добавить предмет!\n";
        return false;
    }

    m_items[m_size++] = item;
    return true;
}

Item* Inventory::RemoveItem(std::size_t index)
{
    if (index >= m_size)
    {
        std::cout << "[Инвентарь] Ошибка: неверный индекс для удаления!\n";
        return nullptr;
    }

    Item* removed = m_items[index];

    std::rotate(m_items.begin() + index,
                m_items.begin() + index + 1,
                m_items.begin() + m_size);
    m_items[--m_size] = nullptr;

    return removed;
}

const Item* Inventory::GetItem(std::size_t index) const
{
    return index < m_size ? m_items.at(index) : nullptr;
}

void Inventory::PrintItems() const
{
    std::cout << "--- Инвентарь (" << m_size << "/" << m_items.size() << ") ---\n";

    std::size_t slot = 0;
    for (auto it = m_items.begin(); it != m_items.begin() + m_size; ++it, ++slot)
    {
        std::cout << " Слот " << slot << ": " << (*it)->GetName() << "\n";
    }
}

} // namespace game
