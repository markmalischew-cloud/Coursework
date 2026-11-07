//
// ФАЙЛ room.hpp
//
#pragma once

#include <string>
#include <string_view>

namespace game
{

class BaseHero;

class Room
{
public:
    explicit Room(std::string_view name);
    Room(const Room&)            = delete;
    Room(Room&&)                 = delete;
    Room& operator=(const Room&) = delete;
    Room& operator=(Room&&)      = delete;
    ~Room();

    void Rename(std::string_view name);

    // Комната получает героя по ссылке: ей нужно только прочитать его данные
    void Welcome(const BaseHero& hero) const;

    [[nodiscard]] std::string_view GetName() const { return m_name; }

private:
    std::string m_name;
};

} // namespace game
