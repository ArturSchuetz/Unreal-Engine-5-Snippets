// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashScreenUserWidget.h"
#include "Components/Image.h"

USplashScreenUserWidget::USplashScreenUserWidget(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer),
	BlackOverlayImage(nullptr),
	LogoImage(nullptr),
	FadeTime(1.0f),
	LogoDisplayTime(3.0f),
	CurrentFadingTime(0.0f),
	CurrentDisplayTime(0.0f),
	CurrentAnimationState(0),
	CurrentLogoIndex(0),
	IsClosing(false)
{

}

void USplashScreenUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	switch (CurrentAnimationState)
	{
	case 0:
	{
		// 2 seconds delay timer before the first image is faded in
		CurrentDisplayTime = 2.0f;
		CurrentAnimationState++;
	}
	break;
	case 1:
	{
		// wait till the timer reaches zero
		if (CurrentDisplayTime >= 0.0f)
		{
			CurrentDisplayTime -= InDeltaTime;
		}
		else
		{
			CurrentAnimationState++;
		}
	}
	break;
	case 2:
	{
		// check if images exists in the designer and set images to visible
		if (BlackOverlayImage != nullptr)
		{
			BlackOverlayImage->SetVisibility(ESlateVisibility::Visible);
		}

		if (LogoImage != nullptr)
		{
			// if we have images to show overwrite current brush with texture from the array we filled in the editor
			if (CurrentLogoIndex < Images.Num())
			{
				LogoImage->SetBrushFromTexture(Images[CurrentLogoIndex++], true);
			}

			// set images to visible
			LogoImage->SetVisibility(ESlateVisibility::Visible);
		}

		// initialize the next animation state
		CurrentFadingTime = FadeTime;
		CurrentAnimationState++;
	}
	break;
	case 3:
	{
		// calcualte new opacity of black overlay image for this frame
		float CurrentBlackOverlayOpacity = 1.0f;
		if (CurrentFadingTime >= 0.0f && FadeTime >= 0.0f)
		{
			CurrentFadingTime -= InDeltaTime;
			CurrentBlackOverlayOpacity = FMath::Lerp(0.0f, 1.0f, CurrentFadingTime / FadeTime);
		}
		else
		{
			// initialize the next animation state
			CurrentFadingTime = 0.0f;
			CurrentBlackOverlayOpacity = 0.0f;
			CurrentDisplayTime = LogoDisplayTime;
			CurrentAnimationState++;
		}

		// actually set the new opacity of our black overlay image with our calculated value
		if (BlackOverlayImage != nullptr)
		{
			BlackOverlayImage->SetOpacity(CurrentBlackOverlayOpacity);
		}
	}
	break;
	case 4:
	{
		if (CurrentDisplayTime >= 0.0f && LogoDisplayTime >= 0.0f)
		{
			CurrentDisplayTime -= InDeltaTime;
		}
		else
		{
			// initialize the next animation state
			CurrentDisplayTime = 0.0f;
			CurrentFadingTime = FadeTime;
			CurrentAnimationState++;
		}
	}
	break;
	case 5:
	{
		// calcualte new opacity of black overlay image for this frame
		float CurrentBlackOverlayOpacity = 1.0f;
		if (CurrentFadingTime >= 0.0f && FadeTime >= 0.0f)
		{
			CurrentFadingTime -= InDeltaTime;
			CurrentBlackOverlayOpacity = FMath::Lerp(1.0f, 0.0f, CurrentFadingTime / FadeTime);
		}
		else
		{
			// initialize the next animation state
			CurrentFadingTime = 0.0f;
			CurrentBlackOverlayOpacity = 1.0f;
			CurrentDisplayTime = LogoDisplayTime;

			// ff we still have Images to show, just jump to the fading in animation state
			if (CurrentLogoIndex < Images.Num())
			{
				CurrentAnimationState = 2;
			}
			else
			{
				// switch to next animation state
				CurrentAnimationState++;
			}
		}

		// actually set the new opacity of our black overlay image with our calculated value
		if (BlackOverlayImage != nullptr)
		{
			BlackOverlayImage->SetOpacity(CurrentBlackOverlayOpacity);
		}
	}
	break;
	case 6:
	{
		// Transition to MainMenu
	}
	break;
	}

	// Call the super function to preseve normal widget behaviour
	return Super::NativeTick(MyGeometry, InDeltaTime);
}

FReply USplashScreenUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// if we press a mouse button, jump to the end of the current displayed image
	if (!IsClosing)
	{
		IsClosing = true;
		CurrentFadingTime = FadeTime;
		CurrentAnimationState = 5;
	}

	// Call the super function to preseve normal widget behaviour
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply USplashScreenUserWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// if we press a key, jump to the end of the current displayed image
	if (!IsClosing)
	{
		IsClosing = true;
		CurrentFadingTime = FadeTime;
		CurrentAnimationState = 5;
	}

	// Call the super function to preseve normal widget behaviour
	return Super::NativeOnKeyUp(InGeometry, InKeyEvent);
}