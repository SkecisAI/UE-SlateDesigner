// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISlateWrapper.h"

/**
 * 
 */

class SLATEDESIGNER_API SVerticalBoxWrapper : public ISlateWrapper
{
public:
	virtual void AddSlot(TSharedPtr<SWidget> ChildWidget) override;
	
	virtual void AddSlotAttrbute(const FString& AttributeLine) override;

	SVerticalBoxWrapper();
	
	virtual void SetAttribute(const FString& AttrLine) override;
	
	virtual TSharedPtr<SWidget> GetWidget() override;

private:
	TSharedPtr<SVerticalBox> Widget;

	TArray<FString> SlotAttributeLines;
};
