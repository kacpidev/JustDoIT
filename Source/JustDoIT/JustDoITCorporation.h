// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JustDoITActor.h"
#include "GameFramework/Actor.h"
#include "JustDoITWorkplace.h"
#include "JustDoITPrinter.h"
#include <Runtime/Core/Public/Containers/Array.h>
#include <Runtime/Engine/Public/EngineUtils.h>
#include "JustDoITCorporation.generated.h"

UCLASS()
class JUSTDOIT_API AJustDoITCorporation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJustDoITCorporation();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void EarnSomeMoney(const float& money);
	
public:
	float TotalMoneyEarned;
	TArray<TActorIterator<AJustDoITWorkplace>> WorkplacesVector;
	TArray<TActorIterator<AJustDoITPrinter>> PrinterVector;
	float UpdateMoneyTime;
	float OtherTime;
	float IssueTime;
	float IssueRandTime;

	UPROPERTY(BlueprintReadWrite)
		int32 ExclamationMarks;
};
