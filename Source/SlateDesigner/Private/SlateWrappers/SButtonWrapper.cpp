// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWrappers/SButtonWrapper.h"

#include "SlateWrappers/AttributeConverter.h"


void SButtonWrapper::AddSlot(TSharedPtr<SWidget> ChildWidget)
{
	Widget->SetContent(ChildWidget.ToSharedRef());
}

SButtonWrapper::SButtonWrapper()
{
	Widget = SNew(SButton);
}

void SButtonWrapper::SetAttribute(const FString& AttrLine)
{
	if (AttrLine.StartsWith(".HAlign("))
	{
		Widget->SetHAlign(FEnumConverter<EHorizontalAlignment>::Convert(AttrLine));
	}
	else if (AttrLine.StartsWith(".VAlign("))
	{
		Widget->SetVAlign(FEnumConverter<EVerticalAlignment>::Convert(AttrLine));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Ignore Attribute for SButton: %s"), *AttrLine);
	}
}

TSharedPtr<SWidget> SButtonWrapper::GetWidget()
{
	return Widget;
}
