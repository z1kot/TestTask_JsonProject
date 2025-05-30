#pragma once

#include "CoreMinimal.h"

class FColorNameParser
{
public:
    /* Dictionary of FColor/color name */
    inline static const TMap<FString, FColor> ColorDictionary 
    {
        { TEXT("black"),   FColor::Black   },
        { TEXT("white"),   FColor::White   },
        { TEXT("red"),     FColor::Red     },
        { TEXT("green"),   FColor::Green   },
        { TEXT("blue"),    FColor::Blue    },
        { TEXT("yellow"),  FColor::Yellow  },
        { TEXT("cyan"),    FColor::Cyan    },
        { TEXT("magenta"), FColor::Magenta },
        { TEXT("orange"),  FColor(255,165,0)},
        { TEXT("purple"),  FColor(128,0,128)},
        { TEXT("gray"),    FColor(128,128,128)},
    };

    /* Get FColor from color name */
    static FColor FromName(const FString& Name);

    /* Find nearest color name to FColor */
    static FString GetNearestColorName(const FColor& InColor);

    /* Random FColor from dictionary */
    static FColor RandomColorFromDictionary();
};