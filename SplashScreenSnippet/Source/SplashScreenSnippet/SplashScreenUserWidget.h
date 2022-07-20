// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SplashScreenUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPLASHSCREENSNIPPET_API USplashScreenUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	USplashScreenUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	// Image widghet which is created inside the designer
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))
	class UImage* BlackOverlayImage;

	// Image widghet which is created inside the designer
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))
	class UImage* LogoImage;

	// Array of images to show (Can be changed within the editor)
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<class UTexture2D*> Images;

	// Black Overlay Fading Time (Can be changed within the editor)
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float FadeTime;

	// Logo Display Time (Can be changed within the editor)
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float LogoDisplayTime;

	// Variables which are used internally
	float CurrentFadingTime;
	float CurrentDisplayTime;

	int CurrentAnimationState;
	int CurrentLogoIndex;

	bool IsClosing;
};
