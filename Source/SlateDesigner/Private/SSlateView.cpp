// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlateView.h"

#include "SlateOptMacros.h"
#include "SSlateCodeEditor.h"
#include "SlateWrappers/ISlateWrapper.h"
#include "SlateWrappers/SBoxWrapper.h"
#include "SlateWrappers/SButtonWrapper.h"
#include "SlateWrappers/SHorizontalBoxWrapper.h"
#include "SlateWrappers/STextBlockWrapper.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "Widgets/Layout/SGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SlateViewSpace"

void SSlateView::Construct(const FArguments& InArgs, TSharedPtr<SSlateCodeEditor> InSlateCodeEditor)
{
	SlateCodeEditor = InSlateCodeEditor;

	SlateCodeEditor->OnSlateTextChanged.BindRaw(this, &SSlateView::OnSlateCodeTextChanged);

	EmptyWidget = SNew(STextBlock)
		.Font(FCoreStyle::GetDefaultFontStyle(FName("Regular"), 15))
		.Text(LOCTEXT("EmptyWidgetText", "Empty Widget"));
	
	SDesignSurface::Construct(SDesignSurface::FArguments()
		.AllowContinousZoomInterpolation(true)
		.Content()
		[
			SNew(SBox)
			.HeightOverride(600.0f)
			.WidthOverride(600.0f)
			[
				SNew(SGridPanel)
				.FillColumn(1, 1.0f)
				.FillRow(1, 1.0f)

				// Corner
				+ SGridPanel::Slot(0, 0)
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
					.BorderBackgroundColor(FLinearColor(FColor(50, 50, 50)))
				]
				+ SGridPanel::Slot(1, 1)
				[
					SNew(SOverlay)
					.Visibility(EVisibility::Visible)
					.Clipping(EWidgetClipping::ClipToBoundsAlways)

					+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SBorder)
						.Padding(FMargin(0))
						[
							SNew(SDPIScaler)
							[
								SAssignNew(PreviewWidgetBox, SBox)
							]
						]
						
					]
				]
			]
		]
	);
}

void SSlateView::OnSlateCodeTextChanged(FText Text)
{
	SlateStringLines.Empty();
	FString SlateString = Text.ToString();
	SlateString.ParseIntoArray(SlateStringLines, LINE_TERMINATOR, true);

	int StartIndex = 0;
	PreviewWidgetBox->SetContent(TranslateSlateRecursively(StartIndex));
}


TSharedRef<SWidget> SSlateView::TranslateSlateRecursively(int& CurLineIndex)
{
	TSharedPtr<ISlateWrapper> Wrapper = nullptr;

	while (CurLineIndex < SlateStringLines.Num())
	{
		FString Line = SlateStringLines[CurLineIndex].TrimStart();
        
		if (Line.StartsWith("SNew") || Line.StartsWith("SAssignNew"))
		{
			FRegexPattern Pattern(TEXT(".*[, (]+(.*)\\)"));
			FRegexMatcher Matcher(Pattern, Line);

			if (Matcher.FindNext())
			{
				const FString SlateName = Matcher.GetCaptureGroup(1);
				if (SlateName.Equals("SBox"))
				{
					Wrapper = MakeShared<SBoxWrapper>();
				}
				else if (SlateName.Equals("SHorizontalBox"))
				{
					Wrapper = MakeShared<SHorizontalBoxWrapper>();
				}
				else if (SlateName.Equals("SButton"))
				{
					Wrapper = MakeShared<SButtonWrapper>();
				}
				else if (SlateName.Equals("STextBlock"))
				{
					Wrapper = MakeShared<STextBlockWrapper>();
				}

				UE_LOG(LogTemp, Warning, TEXT("*** Slate Find: %s ***"), *SlateName);
			}
			else
			{
				break;
			}
            
		}
		else if (Line.StartsWith("."))
		{
			if (Wrapper.IsValid())
			{
				Wrapper->SetAttribute(Line);
			}
		}
		else if (Line.StartsWith("+") && Line.EndsWith("::Slot()"))
		{
			while (CurLineIndex < SlateStringLines.Num() && !SlateStringLines[CurLineIndex].Contains("["))
			{
				if (SlateStringLines[CurLineIndex].StartsWith("."))
				{
					Wrapper->AddSlotAttrbute(SlateStringLines[CurLineIndex]);
				}
				++ CurLineIndex;
			}
			
			continue;
		}
		else if (Line.StartsWith("["))
		{
			if (Wrapper.IsValid())
			{
				++ CurLineIndex;
				TSharedPtr<SWidget> Widget = TranslateSlateRecursively(CurLineIndex);
				Wrapper->AddSlot(Widget);
				Wrapper->SetSlotAttributes();
			}
		}
		else if (Line.StartsWith("]"))
		{
			break;
		}

		++ CurLineIndex;
	}
    
	return Wrapper.IsValid() ? Wrapper->GetWidget().ToSharedRef() : EmptyWidget.ToSharedRef();
}

int32 SSlateView::GetSnapGridSize() const
{
	return 10;
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
