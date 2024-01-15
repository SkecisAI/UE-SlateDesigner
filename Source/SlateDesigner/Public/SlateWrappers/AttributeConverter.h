// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FMarginConverter
{
	static FMargin Convert(const FString& Str)
	{
		FRegexPattern Pattern(TEXT("[0-9]+[.]?[0-9]*"));
		FRegexMatcher Matcher(Pattern, Str);
		TArray<FString> PaddingComps;
		while (Matcher.FindNext())
		{
			PaddingComps.Add(Matcher.GetCaptureGroup(0));
		}

		if (PaddingComps.Num() == 1)
		{
			return FMargin(FCString::Atof(*PaddingComps[0]));
		}
		else if (PaddingComps.Num() == 2)
		{
			return  FMargin(FCString::Atof(*PaddingComps[0]), FCString::Atof(*PaddingComps[1]));
		}
		else if (PaddingComps.Num() == 4)
		{
			return  FMargin(
				FCString::Atof(*PaddingComps[0]),
				FCString::Atof(*PaddingComps[1]),
				FCString::Atof(*PaddingComps[2]),
				FCString::Atof(*PaddingComps[3]));
		}

		return FMargin();
	}
};

struct FFloatConverter
{
	static float Convert(const FString& Str)
	{
		FRegexPattern Pattern(TEXT("[0-9]+[.]?[0-9]*"));
		FRegexMatcher Matcher(Pattern, Str);
		if (Matcher.FindNext())
		{
			return FCString::Atof(*Matcher.GetCaptureGroup(0));
		}

		return 0.01f;
	}
};

template<typename EnumType>
struct FEnumConverter
{
	static EnumType Convert(const FString& Str)
	{
		UEnum* Enum = StaticEnum<EnumType>();
		if (!Enum) return static_cast<EnumType>(0);

		FRegexPattern Pattern(TEXT(".*\\((.*)\\)"));
		FRegexMatcher Matcher(Pattern, Str);
		if (Matcher.FindNext())
		{
			return static_cast<EnumType>(Enum->GetValueByName(FName(Matcher.GetCaptureGroup(1))));
		}
		return static_cast<EnumType>(0);
	}
};


struct FTextConverter
{
	static FText Convert(const FString& Str)
	{
		FRegexPattern Pattern(TEXT(".*[, (]+\"(.*?)\"\\)"));
		FRegexMatcher Matcher(Pattern, Str);
		if (Matcher.FindNext())
		{
			return FText::FromString(Matcher.GetCaptureGroup(1));
		}

		return FText();
	}
};
