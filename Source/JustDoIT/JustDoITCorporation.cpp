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

	TotalMoneyEarned = 3000.f;
	ExclamationMarks = 0;
	UpdateMoneyTime = 0.f;
	IssueTime = 0.f;
	IssueRandTime = FMath::FRandRange(4.f, 7.f);
}

// Called every frame
void AJustDoITCorporation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int32 exclamations = 0;
	for (auto & i : WorkplacesVector)
	{
		if (!(i->IsWorking()))
			exclamations += 1;
	}

	if (exclamations == 0 || exclamations == 1)
		ExclamationMarks = 0;
	else if (exclamations == 2)
		ExclamationMarks = 1;
	else if (exclamations == 3)
		ExclamationMarks = 2;
	else
		ExclamationMarks = 3;

	ExclamationMarks = exclamations;

	UpdateMoneyTime += DeltaTime;
	IssueTime += DeltaTime;

	if (IssueTime > IssueRandTime)
	{
		IssueTime = 0;
		IssueRandTime = FMath::FRandRange(4.f, 7.f);
		int32 IssueMachine = FMath::RandHelper(WorkplacesVector.Num());
		WorkplacesVector[IssueMachine]->GenerateIssue();

	}

	for (auto & i : WorkplacesVector)
	{

		ProblemsSolved = 0;

		if (!i->IsWorking())
		{
			EarnSomeMoney(-12.f*DeltaTime);
		}
		else
		{
			EarnSomeMoney(3.f*DeltaTime);
		}

		ProblemsSolved += i->ProblemsSolved;
	}

	if (TotalMoneyEarned > 6100.0f)
	{
		TotalMoneyEarned = 6100.0f;
	}
	else if (TotalMoneyEarned < -100.0f)
	{
		TotalMoneyEarned = 100.0f;
	}
}

void AJustDoITCorporation::EarnSomeMoney(const float& money)
{
	TotalMoneyEarned += money;
}