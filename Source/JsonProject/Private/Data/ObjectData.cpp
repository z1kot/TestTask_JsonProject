#include "Data/ObjectData.h"

void UObjectData::Initialize(int32 InId, const FString& InName, const FVector& InPos, const FColor& InColor, bool bActive)
{
    Id = InId; 
    Name = InName; 
    Position = InPos; 
    Color = InColor; 
    bIsActive = bActive;
}

void UObjectData::ToggleActive()
{
    bIsActive = !bIsActive;
    OnStateChanged.Broadcast(this);
}

void UObjectData::SetColor(const FColor& NewColor)
{
    Color = NewColor;
    OnStateChanged.Broadcast(this);
}
