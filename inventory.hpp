//
// ФАЙЛ inventory.hpp
//
#pragma once

#include "item.hpp"

#include <cstddef>
#include <memory>

namespace game
{

class Inventory
{
public:
    Inventory();
    Inventory(const Inventory&)            = delete;
    Inventory(Inventory&&)                 = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory& operator=(Inventory&&)      = delete;
    ~Inventory();

    bool AddItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<Item> RemoveItem(std::size_t index);
    void PrintItems() const;

    [[nodiscard]] std::shared_ptr<Item> GetItem(std::size_t index) const;

    [[nodiscard]] std::size_t GetSize() const
    {
        return m_size;
    }

    [[nodiscard]] static constexpr std::size_t GetCapacity()
    {
        return CAPACITY;
    }

private:
    static constexpr std::size_t CAPACITY = 20;

    std::shared_ptr<Item> m_items[CAPACITY]{};
    std::size_t           m_size{ 0 };
};

} // namespace game
