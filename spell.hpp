//
// ФАЙЛ spell.hpp
//
#pragma once

#include <stdexcept>
#include <string_view>

namespace game
{

enum class SpellElement
{
    eFire,
    eWater,
    eEarth,
    eAir
};

struct SpellInfo
{
    std::string_view name;
    int              damage;
    int              manaCost;
};

[[nodiscard]] constexpr SpellInfo GetSpellInfo(SpellElement element)
{
    switch (element)
    {
        case SpellElement::eFire:  return { "Огонь", 40, 80 };
        case SpellElement::eWater: return { "Вода", 25, 25 };
        case SpellElement::eEarth: return { "Земля", 30, 40 };
        case SpellElement::eAir:   return { "Воздух", 20, 20 };
    }
    throw std::invalid_argument{ "неизвестная стихия" };
}

} // namespace game
