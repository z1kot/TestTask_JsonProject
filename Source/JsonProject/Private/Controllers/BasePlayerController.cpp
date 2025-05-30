#include "Controllers/BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/ObjectsManager.h"
#include "Actors/InteractiveActor.h"
#include "UI/ObjectListWidget.h"
#include "Utils/ColorNameParser.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

    // Controller
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

    // Model
    Manager = GetWorld()->SpawnActor<AObjectsManager>(ObjectsManagerClass, FVector::ZeroVector, FRotator::ZeroRotator);
    Manager->Init();

    // View and Controller too
    ListWidget = CreateWidget<UObjectListWidget>(this, ListWidgetClass);
    ListWidget->AddToViewport();
    ListWidget->InitializeWithManager(Manager);
}

void ABasePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABasePlayerController::OnInteract);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
    }
}

void ABasePlayerController::OnInteract()
{
    FHitResult Hit;
    int32 X, Y;
    GetViewportSize(X, Y);
    GetHitResultAtScreenPosition(FVector2D(X / 2.0f, Y / 2.0f), ECC_Visibility, false, Hit);
    if (AInteractiveActor* Actor = Cast<AInteractiveActor>(Hit.GetActor()))
    {
        Actor->Data->SetColor(FColorNameParser::RandomColorFromDictionary());
    }
}