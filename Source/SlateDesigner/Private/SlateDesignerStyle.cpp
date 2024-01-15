// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateDesignerStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> SlateDesignerStyle::StyleInstance = nullptr;
TArray<UObject*> SlateDesignerStyle::StyleObject;

TSharedRef<FSlateStyleSet> SlateDesignerStyle::CreateStyle()
{
	StyleInstance = MakeShareable(new FSlateStyleSet(GetStyleName()));

	return StyleInstance.ToSharedRef();
}

void SlateDesignerStyle::Initilize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = CreateStyle();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}

	UObject* Font = StaticLoadObject(nullptr, nullptr, TEXT("/SlateDesigner/ConsolaFont.ConsolaFont"));
	StyleInstance->Set("SlateDesigner.SlateText", FSlateFontInfo(Font, 14, TEXT("Default")));
	
}

void SlateDesignerStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);

	for (UObject* Object : StyleObject)
	{
		Object->RemoveFromRoot();
	}
}

TSharedRef<FSlateStyleSet> SlateDesignerStyle::GetStyle()
{
	return StyleInstance.ToSharedRef();
}

FName SlateDesignerStyle::GetStyleName()
{
	static FName SlateDesignerStyleName(TEXT("SlateDesignerStyle"));

	return SlateDesignerStyleName;
}
