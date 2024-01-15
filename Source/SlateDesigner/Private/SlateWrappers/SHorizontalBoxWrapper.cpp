// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWrappers/SHorizontalBoxWrapper.h"


void SHorizontalBoxWrapper::AddSlot(TSharedPtr<SWidget> ChildWidget)
{
	auto& Slot = Widget->AddSlot()[ChildWidget.ToSharedRef()];
	
}

void SHorizontalBoxWrapper::AddSlotAttrbute(const FString& AttributeLine)
{
	SlotAttributeLines.Add(AttributeLine);
}

void SHorizontalBoxWrapper::SetSlotAttributes()
{
	
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
