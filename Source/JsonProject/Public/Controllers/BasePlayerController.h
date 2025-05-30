// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AObjectsManager;
class UObjectListWidget;

UCLASS()
class JSONPROJECT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

	/* PROPERTIES */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Objects System")
	TSubclassOf<AObjectsManager> ObjectsManagerClass;
	AObjectsManager* Manager;

	UPROPERTY(EditDefaultsOnly, Category = "Objects System")
	TSubclassOf<UObjectListWidget> ListWidgetClass;
	UObjectListWidget* ListWidget;

	/* FUNCTIONS */
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/* Find object in fron of camera and set random color */
	void OnInteract();
};
