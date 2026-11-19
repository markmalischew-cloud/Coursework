//
// ФАЙЛ monster_tactics.hpp
//
#pragma once

#include "i_monster_tactic.hpp"

#include <stdexcept>

namespace game
{

// Всегда атакует
class AggressiveTactic final : public IMonsterTactic
{
public:
    [[nodiscard]] MonsterAction Decide(int /*healthPercent*/) const override
    {
        return MonsterAction::eAttack;
    }

    [[nodiscard]] std::string_view GetName() const override { return "агрессивная"; }
};

// Убегает, когда здоровья меньше порога
class CowardlyTactic final : public IMonsterTactic
{
public:
    explicit CowardlyTactic(int thresholdPercent)
        : m_thresholdPercent{ thresholdPercent }
    {
        if (thresholdPercent < 0 || thresholdPercent > 100)
        {
            throw std::invalid_argument{ "порог здоровья должен быть от 0 до 100 процентов" };
        }
    }

    [[nodiscard]] MonsterAction Decide(int healthPercent) const override
    {
        return healthPercent < m_thresholdPercent ? MonsterAction::eFlee : MonsterAction::eAttack;
    }

    [[nodiscard]] std::string_view GetName() const override { return "трусливая"; }

private:
    int m_thresholdPercent;
};

// Просит пощады, когда здоровья меньше порога
class BeggingTactic final : public IMonsterTactic
{
public:
    explicit BeggingTactic(int thresholdPercent)
        : m_thresholdPercent{ thresholdPercent }
    {
        if (thresholdPercent < 0 || thresholdPercent > 100)
        {
            throw std::invalid_argument{ "порог здоровья должен быть от 0 до 100 процентов" };
        }
    }

    [[nodiscard]] MonsterAction Decide(int healthPercent) const override
    {
        return healthPercent < m_thresholdPercent ? MonsterAction::eBegForMercy : MonsterAction::eAttack;
    }

    [[nodiscard]] std::string_view GetName() const override { return "просящая пощады"; }

private:
    int m_thresholdPercent;
};

} // namespace game
