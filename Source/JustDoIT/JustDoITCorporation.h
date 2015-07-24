// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "JustDoITCorporation.generated.h"

/**
 * 
 */
UCLASS()
class JUSTDOIT_API UJustDoITCorporation : public UObject
{
	GENERATED_BODY ()
	

public:
	UJustDoITCorporation ();
	void EarnSomeMoney (const float& money);

public: 
	float TotalMoneyEarned;
};
