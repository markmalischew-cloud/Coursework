//
// ФАЙЛ inventory.cpp
//

#include "inventory.hpp"
#include <iostream>

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
    if (item == nullptr || m_size >= CAPACITY)
    {
        std::cout << "[Инвентарь] Ошибка: не удалось добавить предмет!\n";
        return false;
    }

    m_items[m_size] = item;
    ++m_size;
    return true;
}

bool Inventory::RemoveItem(std::size_t index)
{
    if (index >= m_size || m_items[index] == nullptr)
    {
        std::cout << "[Инвентарь] Ошибка: неверный индекс для удаления!\n";
        return false;
    }

    m_items[index] = m_items[m_size - 1];
    m_items[m_size - 1] = nullptr;

    --m_size;
    return true;
}

const Item* Inventory::GetItem(std::size_t index) const
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
        if (m_items[i] != nullptr)
        {
            std::cout << " Слот " << i << ": " << m_items[i]->GetName() << "\n";
        }
    }
}

} // namespace game
