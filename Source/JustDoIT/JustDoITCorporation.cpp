// Fill out your copyright notice in the Description page of Project Settings.

#include "JustDoIT.h"
#include "JustDoITCorporation.h"
#include <Runtime/Engine/Public/Engine.h>


// Sets default values
AJustDoITCorporation::AJustDoITCorporation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TotalMoneyEarned = 0;
}

// Called when the game starts or when spawned
void AJustDoITCorporation::BeginPlay()
{
	Super::BeginPlay();
	for (auto workplace : WorkplacesVector)
	{
		//WorkplacesVector.(ActorItr);
		WorkplacesVector.Add(workplace);
	}
	UpdateMoneyTime = 0.f;
}

// Called every frame
void AJustDoITCorporation::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UpdateMoneyTime += DeltaTime;
	OtherTime += DeltaTime;

	if (UpdateMoneyTime > 0.5f)
	{
		UpdateMoneyTime = 0;
		for (auto & i : WorkplacesVector)
		{
			if (i->IsWorking())
				EarnSomeMoney(3.f);
		}
	}
	
	TotalMoneyEarned -= 0.05f * DeltaTime;
	
	if (OtherTime > 10.f)
	{
		OtherTime = 0.f;
		FString TheFloatStr = FString::SanitizeFloat(TotalMoneyEarned);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *TheFloatStr);
		}
	}
}

void AJustDoITCorporation::EarnSomeMoney(const float& money)
{
	TotalMoneyEarned += money;
}