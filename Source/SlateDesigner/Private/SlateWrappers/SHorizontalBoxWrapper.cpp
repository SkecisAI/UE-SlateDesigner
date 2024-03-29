﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWrappers/SHorizontalBoxWrapper.h"

#include "SlateWrappers/AttributeConverter.h"


void SHorizontalBoxWrapper::AddSlot(TSharedPtr<SWidget> ChildWidget)
{
	Widget->AddSlot()[ChildWidget.ToSharedRef()];
	auto& Slot = Widget->GetSlot(Widget->NumSlots() - 1);

	for (const FString& AttributeLine : SlotAttributeLines)
	{
		if (AttributeLine.StartsWith(".Padding("))
		{
			Slot.SetPadding(FMarginConverter::Convert(AttributeLine));
		}
		else if (AttributeLine.StartsWith(".HAlign("))
		{
			Slot.SetHorizontalAlignment(FEnumConverter<EHorizontalAlignment>::Convert(AttributeLine));
		}
		else if (AttributeLine.StartsWith(".VAlign("))
		{
			Slot.SetVerticalAlignment(FEnumConverter<EVerticalAlignment>::Convert(AttributeLine));
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Ignore Attribute for SHorizontalBox: %s"), *AttributeLine);
		}
	}

	SlotAttributeLines.Empty();
}

void SHorizontalBoxWrapper::AddSlotAttrbute(const FString& AttributeLine)
{
	SlotAttributeLines.Add(AttributeLine);
}

SHorizontalBoxWrapper::SHorizontalBoxWrapper()
{
	Widget = SNew(SHorizontalBox);
}

void SHorizontalBoxWrapper::SetAttribute(const FString& AttrLine)
{
}

TSharedPtr<SWidget> SHorizontalBoxWrapper::GetWidget()
{
	return Widget;
}
