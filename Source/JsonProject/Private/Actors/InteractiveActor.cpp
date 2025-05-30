#include "Actors/InteractiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Data/ObjectData.h"

AInteractiveActor::AInteractiveActor()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
}

void AInteractiveActor::Initialize(UObjectData* InData)
{
    Data = InData;
    SetActorLocation(Data->Position);

    SetMeshByName(Data->Name);

    if (MeshComp)
    {
        DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
        MeshComp->SetMaterial(0, DynamicMaterial);
    }

    OnDataChanged(nullptr);

    Data->OnStateChanged.AddUObject(this, &AInteractiveActor::OnDataChanged);
}

void AInteractiveActor::BeginPlay()
{
    Super::BeginPlay();
}

void AInteractiveActor::OnDataChanged(UObject* Object)
{
    if (DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue(TEXT("Color"), Data->Color.ReinterpretAsLinear());
    }

    MeshComp->SetVisibility(Data->bIsActive);
}
