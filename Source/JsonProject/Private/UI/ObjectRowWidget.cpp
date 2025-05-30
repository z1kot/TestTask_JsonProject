#include "UI/ObjectRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "Utils/ColorNameParser.h"

void UObjectRowWidget::InitializeWithData(UObjectData* InData)
{
    Data = InData;
    NameText->SetText(FText::FromString(Data->Name));
    ColorText->SetText(FText::FromString(FColorNameParser::GetNearestColorName(Data->Color)));
    ActiveCheckbox->SetIsChecked(Data->bIsActive);
    ActiveCheckbox->OnCheckStateChanged.AddDynamic(this, &UObjectRowWidget::OnCheckboxChanged);

    Data->OnStateChanged.AddLambda([this](UObject*) 
    {
        ActiveCheckbox->SetIsChecked(Data->bIsActive);
        ColorText->SetText(FText::FromString(FColorNameParser::GetNearestColorName(Data->Color)));
    });
}

void UObjectRowWidget::OnCheckboxChanged(bool bChecked)
{
    Data->ToggleActive();
}
