#include "UI/ObjectListWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "UI/ObjectRowWidget.h"
#include "Data/ObjectsManager.h"

void UObjectListWidget::NativeConstruct()
{
    Super::NativeConstruct();

    FinishButton->OnClicked.AddDynamic(this, &UObjectListWidget::OnFinishClicked);
}

void UObjectListWidget::InitializeWithManager(AObjectsManager* InManager)
{
    Manager = InManager;
    ListContainer->ClearChildren();
    for (UObjectData* ObjectData : Manager->Objects)
    {
        UObjectRowWidget* Row = CreateWidget<UObjectRowWidget>(this, RowClass);
        Row->InitializeWithData(ObjectData);
        ListContainer->AddChild(Row);
    }
}

void UObjectListWidget::OnFinishClicked()
{
    if (Manager->SaveToJson())
    {
        UE_LOG(LogTemp, Warning, TEXT("Objects Data successfully saved to json"));
    }
}
