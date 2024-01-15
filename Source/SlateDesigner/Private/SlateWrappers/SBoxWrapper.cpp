// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWrappers/SBoxWrapper.h"
#include "SlateWrappers/AttributeConverter.h"


void SBoxWrapper::AddSlot(TSharedPtr<SWidget> ChildWidget)
{
	Widget->SetContent(ChildWidget.ToSharedRef());
}

void SBoxWrapper::SetAttribute(const FString& AttrLine)
{
	if (AttrLine.StartsWith(".Padding("))
	{
		Widget->SetPadding(FMarginConverter::Convert(AttrLine));
	}
	else if (AttrLine.StartsWith(".HeightOverride("))
	{
		Widget->SetHeightOverride(FFloatConverter::Convert(AttrLine));
	}
	else if (AttrLine.StartsWith(".WidthOverride("))
	{
		Widget->SetWidthOverride(FFloatConverter::Convert(AttrLine));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Ignore Attribute for SBox: %s"), *AttrLine);
	}
}

TSharedPtr<SWidget> SBoxWrapper::GetWidget()
{
	return Widget;
}


SBoxWrapper::SBoxWrapper()
{
	Widget = SNew(SBox);
}
