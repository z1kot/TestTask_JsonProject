#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ObjectData.h"
#include "ObjectRowWidget.generated.h"

class UTextBlock;
class UCheckBox;

UCLASS()
class JSONPROJECT_API UObjectRowWidget : public UUserWidget
{
    GENERATED_BODY()

    /* PROPERTIES */
public:
    UPROPERTY(meta = (BindWidget)) 
    UTextBlock* NameText;
    UPROPERTY(meta = (BindWidget)) 
    UTextBlock* ColorText;
    UPROPERTY(meta = (BindWidget)) 
    UCheckBox* ActiveCheckbox;

private:
    UObjectData* Data;

    /* FUNCTIONS */
public:
    void InitializeWithData(UObjectData* InData);

private:
    UFUNCTION()
    void OnCheckboxChanged(bool bChecked);
};
