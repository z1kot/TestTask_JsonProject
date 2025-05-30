#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveActor.generated.h"

class UObjectData;

UCLASS()
class JSONPROJECT_API AInteractiveActor : public AActor
{
    GENERATED_BODY()

    AInteractiveActor();

    /* PROPERTIES */
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComp;
    UMaterialInstanceDynamic* DynamicMaterial;

    UObjectData* Data;

    /* FUNCTIONS */
public:
    void Initialize(UObjectData* InData);

    /* In blueprints implement event, which will assign static mesh by name from data */
    /* For test supports: Box1, Sphere1, Cone, Cylinder */
    UFUNCTION(BlueprintImplementableEvent)
    void SetMeshByName(const FString& MeshName);

protected:
    UFUNCTION()
    void OnDataChanged(UObject* Object);

    virtual void BeginPlay() override;
};
