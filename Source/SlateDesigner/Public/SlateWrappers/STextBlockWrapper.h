// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISlateWrapper.h"

/**
 * 
 */
class SLATEDESIGNER_API STextBlockWrapper : public ISlateWrapper
{
public:
	STextBlockWrapper();

	virtual void SetAttribute(const FString& AttrLine) override;
	
	virtual TSharedPtr<SWidget> GetWidget() override;

private:
	TSharedPtr<STextBlock> Widget;
};
