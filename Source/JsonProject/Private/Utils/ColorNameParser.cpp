#include "ColorNameParser.h"

FColor FColorNameParser::FromName(const FString& Name)
{
    FString Key = Name.ToLower();
    if (const FColor* Found = ColorDictionary.Find(Key))
    {
        return *Found;
    }

    return FColor::White;
}

FString FColorNameParser::GetNearestColorName(const FColor& InColor)
{
    double BestDist = DBL_MAX;
    FString BestName = TEXT("Unknown");

    // Iterate through all pairs and try to find nearest color name
    for (auto& Pair : ColorDictionary)
    {
        const FColor& C = Pair.Value;

        double dR = double(InColor.R) - C.R;
        double dG = double(InColor.G) - C.G;
        double dB = double(InColor.B) - C.B;
        double DistSq = dR * dR + dG * dG + dB * dB;

        if (DistSq < BestDist)
        {
            BestDist = DistSq;
            BestName = Pair.Key;
        }
    }
    return BestName;
}

FColor FColorNameParser::RandomColorFromDictionary()
{
    const int32 RandomIndex = FMath::RandRange(0 , ColorDictionary.Num());
    auto It = ColorDictionary.CreateConstIterator();

    for (int32 i = 0; i < RandomIndex; ++i)
    {
        ++It;
    }

    return It->Value;
}