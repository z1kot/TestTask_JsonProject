#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectData.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChanged, UObject*);

UCLASS(BlueprintType)
class JSONPROJECT_API UObjectData : public UObject
{
    GENERATED_BODY()

    /* PROPERTIES */
public:
    UPROPERTY(BlueprintReadOnly) 
    int32 Id;
    UPROPERTY(BlueprintReadOnly) 
    FString Name;
    UPROPERTY(BlueprintReadOnly) 
    FVector Position;
    UPROPERTY(BlueprintReadOnly) 
    FColor Color;
    UPROPERTY(BlueprintReadOnly) 
    bool bIsActive;

    FOnStateChanged OnStateChanged;

    /* FUNCTIONS */
public:
    void Initialize(int32 InId, const FString& InName, const FVector& InPos, const FColor& InColor, bool bActive);

    /* Toggle object visibility on scene */
    void ToggleActive();

    /* Color for mesh on scene */
    void SetColor(const FColor& NewColor);
};