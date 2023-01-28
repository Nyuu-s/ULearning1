#pragma once
#include "DrawDebugHelpers.h"

#define DSPHERE(Location)   if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true);
#define DCSPHERE(Location, Color)   if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 8.f, 12, Color, false, 5.f);
#define DSPHERE_SF(Location)   if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, false, -1.f);

#define DLINE(Start, End)   if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f, 0, 2.f);
#define DLINE_SF(Start, End)   if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.f, 0, 2.f);

#define DPOINT(Location)    if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true);
#define DPOINT_SF(Location)    if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, false,-1.f);

#define DBOX(Center, Extent)   if(GetWorld()) DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, true, -1.f,0,1.f);
#define DBOX_SF(Center, Extent)   if(GetWorld()) DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, false, -1.f,0,1.f);

#define DVECTOR(Start, End) if(GetWorld()) \
	{\
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f, 0, 2.f); \
		DrawDebugPoint(GetWorld(), End, 15.f, FColor::Red, true); \
}

#define DVECTOR_SF(Start, End) if(GetWorld()) \
	{\
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.f, 0, 2.f); \
		DrawDebugPoint(GetWorld(), End, 15.f, FColor::Red, false, -1.f); \
}

