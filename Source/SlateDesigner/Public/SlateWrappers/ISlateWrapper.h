// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLATEDESIGNER_API ISlateWrapper
{
public:
	// override
	virtual void AddSlot(TSharedPtr<SWidget> ChildWidget) {}
	virtual void AddSlotAttrbute(const FString& AttributeLine) {}
	// override

	// interface
	virtual void SetAttribute(const FString& AttrLine) = 0;
	virtual TSharedPtr<SWidget> GetWidget() = 0;
	// interface
	
	virtual ~ISlateWrapper() = default;
};
