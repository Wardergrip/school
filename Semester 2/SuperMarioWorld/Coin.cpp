#include "pch.h"
#include "Coin.h"
#include "Texture.h"

Coin::Coin()
	:PickUp(new Texture{"Resources/Coin.png"}, 1, 0.5f)
{
}
