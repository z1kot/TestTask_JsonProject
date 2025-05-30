#include "JsonManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"

bool UJsonManager::LoadJsonObject(const FString& FilePath, TSharedPtr<FJsonObject>& OutObject)
{
    FString JsonStr;
    if (!FFileHelper::LoadFileToString(JsonStr, *FilePath)) 
    {
        UE_LOG(LogTemp, Error, TEXT("Init file load failed, maybe doesn't exist"))
        return false;
    }

    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);
    return FJsonSerializer::Deserialize(Reader, OutObject);
}

bool UJsonManager::SaveJsonObject(const FString& FilePath, const TSharedPtr<FJsonObject>& Object)
{
    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    if (!FJsonSerializer::Serialize(Object.ToSharedRef(), Writer))
    {
        UE_LOG(LogTemp, Error, TEXT("Error during json serialization"))
        return false;
    }

    return FFileHelper::SaveStringToFile(Out, *FilePath);
}

TArray<TSharedPtr<FJsonValue>> UJsonManager::ToJsonArray(const TArray<double>& In)
{
    TArray<TSharedPtr<FJsonValue>> Arr;
    for (double Value : In)
    {
        Arr.Add(MakeShared<FJsonValueNumber>(Value));
    }

    return Arr;
}
