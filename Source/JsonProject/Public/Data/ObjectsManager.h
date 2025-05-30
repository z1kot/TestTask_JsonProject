#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectData.h"
#include "ObjectsManager.generated.h"

class AInteractiveActor;

UCLASS()
class JSONPROJECT_API AObjectsManager : public AActor
{
    GENERATED_BODY()

    /* PROPERTIES */
public:
    UPROPERTY() 
    TArray<UObjectData*> Objects;

    UPROPERTY(EditDefaultsOnly, Category = "Objects System")
    TSubclassOf<AInteractiveActor> InteractiveActorClass;

    /* Initial data JSON file name */
    UPROPERTY(EditDefaultsOnly, Category = "Objects System")
    FString InitDataName = TEXT("init_data");

    /* Save data JSON file name */
    UPROPERTY(EditDefaultsOnly, Category = "Objects System")
    FString SaveDataName = TEXT("objects_state");

    /* FUNCTIONS */
public:
    void Init();
    bool LoadFromJson();
    bool SaveToJson() const;
};
