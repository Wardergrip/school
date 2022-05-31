#include "pch.h"
#include "BasicStats.h"

BasicStats::BasicStats(float maxHealth, float movementSpeed)
    :movementSpeed{movementSpeed}
    ,maxHealth{maxHealth}
    ,currentHealth{maxHealth}
{
}

BasicStats::BasicStats()
    :BasicStats(100,2)
{
}

float BasicStats::GetPercentageHealth() const
{
    return (currentHealth / maxHealth);
}
