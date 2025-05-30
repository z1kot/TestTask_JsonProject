#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ObjectData.h"
#include "ObjectListWidget.generated.h"

class UVerticalBox;
class UButton;
class AObjectsManager;
class UObjectRowWidget;

UCLASS()
class JSONPROJECT_API UObjectListWidget : public UUserWidget
{
    GENERATED_BODY()

    /* PROPERTIES */
public:
    UPROPERTY(meta = (BindWidget)) 
    UVerticalBox* ListContainer;
    UPROPERTY(meta = (BindWidget)) 
    UButton* FinishButton;
    UPROPERTY(EditDefaultsOnly, Category = "Objects System")
    TSubclassOf<UObjectRowWidget> RowClass;

private:
    AObjectsManager* Manager;

    /* FUCNTIONS */
public:
    void InitializeWithManager(AObjectsManager* InManager);

protected:
    virtual void NativeConstruct() override;

private:
    /* User clicks end session to save data to json */
    UFUNCTION()
    void OnFinishClicked();
};
