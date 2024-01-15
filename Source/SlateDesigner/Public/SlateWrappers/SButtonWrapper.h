// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISlateWrapper.h"

/**
 * 
 */
class SLATEDESIGNER_API SButtonWrapper : public ISlateWrapper
{
public:
	SButtonWrapper();
	
	virtual void AddSlot(TSharedPtr<SWidget> ChildWidget) override;

	virtual void SetAttribute(const FString& AttrLine) override;
	
	virtual TSharedPtr<SWidget> GetWidget() override;

private:
	TSharedPtr<SButton> Widget;
};
