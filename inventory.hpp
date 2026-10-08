//
// ФАЙЛ inventory.hpp
// 
#pragma once

#include "item.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <array>
#include <cstddef>

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

        bool AddItem(Item* item);
        bool RemoveItem(std::size_t index);
        void PrintItems() const;

    [[nodiscard]] std::size_t GetSize() const 
    { 
        return m_size; 
    }
    
    [[nodiscard]] static constexpr std::size_t GetCapacity() 
    { 
        return CAPACITY; 
    }

    [[nodiscard]] const Item* GetItem(std::size_t index) const;

    private:
    static constexpr std::size_t CAPACITY = 20;

    std::array<Item*, CAPACITY> m_items{};
    std::size_t                 m_size{ 0 };
    
};


} // namespace game

