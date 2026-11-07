//
// ФАЙЛ inventory.hpp
//
#pragma once

#include "item.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string_view>

namespace game
{

class Inventory
{
public:
    Inventory();
    Inventory(const Inventory& other);
    Inventory(Inventory&& other) noexcept;
    Inventory& operator=(const Inventory& other);
    Inventory& operator=(Inventory&& other) noexcept;
    ~Inventory();

    bool AddItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<Item> RemoveItem(std::size_t index);
    void PrintItems() const;

    // Поиск предмета, в названии которого встречается подстрока
    [[nodiscard]] std::optional<std::size_t> FindItem(std::string_view part) const;

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
    void Clear();

    static constexpr std::size_t CAPACITY = 20;

    std::shared_ptr<Item> m_items[CAPACITY]{};
    std::size_t           m_size{ 0 };
};

} // namespace game
