#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"

class JSONPROJECT_API UJsonManager
{
public:
    static bool LoadJsonObject(const FString& FilePath, TSharedPtr<FJsonObject>& OutObject);
    static bool SaveJsonObject(const FString& FilePath, const TSharedPtr<FJsonObject>& Object);
    static TArray<TSharedPtr<FJsonValue>> ToJsonArray(const TArray<double>& In);
};
