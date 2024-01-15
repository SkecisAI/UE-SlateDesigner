// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWrappers/STextBlockWrapper.h"

#include "SlateWrappers/AttributeConverter.h"


STextBlockWrapper::STextBlockWrapper()
{
	Widget = SNew(STextBlock);
}

void STextBlockWrapper::SetAttribute(const FString& AttrLine)
{
	if (AttrLine.Contains(".Text("))
	{
		Widget->SetText(FTextConverter::Convert(AttrLine));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Ignore Attribute for STextBlock: %s"), *AttrLine);
	}
}

TSharedPtr<SWidget> STextBlockWrapper::GetWidget()
{
	return Widget;
}
