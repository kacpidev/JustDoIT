// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "JustDoITHUD.generated.h"

UCLASS()
class AJustDoITHUD : public AHUD
{
	GENERATED_BODY()

public:
	AJustDoITHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UPROPERTY(BlueprintReadWrite)
		bool bShowCrosshair = false;
	
	UPROPERTY(BlueprintReadWrite)
		bool bInGamePlay = false;

	UPROPERTY(BlueprintReadWrite)
		float GameTime;
	UPROPERTY(BlueprintReadWrite)
		int32 ProblemsSolved;

	UFUNCTION(BlueprintNativeEvent)
		void DrawGamePlayHUD();
private:
	/** Crosshair asset pointer */
		class UTexture2D* CrosshairTex;
};

