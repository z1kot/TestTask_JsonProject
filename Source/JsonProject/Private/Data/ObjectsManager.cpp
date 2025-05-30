#include "Data/ObjectsManager.h"
#include "Utils/JsonManager.h"
#include "Actors/InteractiveActor.h"
#include "Utils/ColorNameParser.h"

void AObjectsManager::Init()
{
    if (!LoadFromJson())
    {
        return;
    }

    for (UObjectData* Data : Objects)
    {
        AInteractiveActor* Actor = GetWorld()->SpawnActor<AInteractiveActor>(InteractiveActorClass, Data->Position, FRotator::ZeroRotator);
        Actor->Initialize(Data);
    }
}

bool AObjectsManager::LoadFromJson()
{
    const FString FilePath = FPaths::ProjectContentDir() / TEXT("Data/") / InitDataName + TEXT(".json");

    TSharedPtr<FJsonObject> Root;
    if (!UJsonManager::LoadJsonObject(FilePath, Root))
    {
        return false;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr;
    if (!Root->TryGetArrayField(TEXT("objects"), Arr))
    {
        UE_LOG(LogTemp, Error, TEXT("Objects array is null, load failed"));
        return false;
    }

    for (auto& Val : *Arr)
    {
        auto Obj = Val->AsObject();
        int32 Id = Obj->GetIntegerField("id");
        FString Name = Obj->GetStringField("name");
        auto PosArr = Obj->GetArrayField("position");
        FVector Pos = FVector(PosArr[0]->AsNumber(), PosArr[1]->AsNumber(), PosArr[2]->AsNumber());
        FColor Col = FColorNameParser::FromName(Obj->GetStringField("color"));
        bool bActive = Obj->GetBoolField("isActive");

        UObjectData* Data = NewObject<UObjectData>(this);
        Data->Initialize(Id, Name, Pos, Col, bActive);
        Objects.Add(Data);
    }

    return true;
}

bool AObjectsManager::SaveToJson() const
{
    const FString SavePath = FPaths::ProjectSavedDir() / SaveDataName + TEXT(".json");

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> Arr;
    for (auto* Data : Objects)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetNumberField("id", Data->Id);
        Obj->SetStringField("name", Data->Name);
        Obj->SetArrayField("position", UJsonManager::ToJsonArray({ Data->Position.X, Data->Position.Y, Data->Position.Z }));
        Obj->SetStringField("color", FColorNameParser::GetNearestColorName(Data->Color));
        Obj->SetBoolField("isActive", Data->bIsActive);
        Arr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    Root->SetArrayField("objects", Arr);
    return UJsonManager::SaveJsonObject(SavePath, Root);
}
