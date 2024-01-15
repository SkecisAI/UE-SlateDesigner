// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLATEDESIGNER_API SlateDesignerStyle
{
private:
	static TSharedPtr<FSlateStyleSet> StyleInstance;

	static TSharedRef<FSlateStyleSet> CreateStyle();

	static TArray<UObject*> StyleObject;

	static FName GetStyleName();
public:

	static void Initilize();
	static void Shutdown();
	static TSharedRef<FSlateStyleSet> GetStyle();

};
