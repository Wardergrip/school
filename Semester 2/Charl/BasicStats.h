#pragma once
struct BasicStats
{
	BasicStats(float maxHealth, float movementSpeed = 2);
	BasicStats();
	float currentHealth;
	float maxHealth;
	// Returns (currentHealth / maxHealth)
	float GetPercentageHealth() const;

	float movementSpeed;
};

