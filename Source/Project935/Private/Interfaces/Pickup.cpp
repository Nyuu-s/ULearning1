// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Pickup.h"

// Add default functionality here for any IPickup functions that are not pure virtual.

void IPickup::SetOverlappingItem(AItem* Item)
{
}

void IPickup::AddSouls(ASoul* Soul)
{
}

void IPickup::AddGold(ATreasure* Gold)
{
}

void IPickup::AddHealth(AHealthPickUp* Heart)
{
}

void IPickup::SetHealth(AHealthPickUp* Heart)
{
}

void IPickup::SetMaxHealth(AHealthPickUp* Heart)
{
}

void IPickup::AddBothHealth(AHealthPickUp* Heart)
{
}
