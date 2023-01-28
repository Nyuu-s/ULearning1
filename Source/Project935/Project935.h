// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define DSPHERE(Location)   if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true);
#define DLINE(Start, End)   if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f, 0, 2.f);
#define DPOINT(Location)    if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true);
#define DVECTOR(Start, End) if(GetWorld()) \
	{\
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f, 0, 2.f); \
		DrawDebugPoint(GetWorld(), End, 15.f, FColor::Red, true); \
}

