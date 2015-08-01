// Fill out your copyright notice in the Description page of Project Settings.

#include "JustDoIT.h"
#include "JustDoITWorkplace.h"
#include <Runtime/Engine/Public/Engine.h>


// Sets default values
AJustDoITWorkplace::AJustDoITWorkplace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJustDoITWorkplace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJustDoITWorkplace::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	bIsWorking = IsWorking();
}

bool AJustDoITWorkplace::IsWorking_Implementation()
{
	if (Computer && CDROM && Wire && Switch)
	{
		return (Computer->ActorState && CDROM->ActorState && Wire->ActorState && Switch->ActorState && Keyboard->ActorState);
	}

	return true;
}

void AJustDoITWorkplace::GenerateIssue()
{
 
	int32 problemSource = FMath::RandHelper(5);

	switch (problemSource)
	{
		case (0):
		{
			if (Computer)
			{
				Computer->ActorState = false;
			}
			break;	
		}
		case (1):
		{
			if (CDROM)
			{
				CDROM->ActorState = false;
			}
			break;
		}
		case (2):
		{
			if (Wire)
			{
				Wire->ActorState = false;
			}
			break;
		}
		case (3):
		{
			if (Switch)
			{
				Switch->ActorState = false;
			}
			break;
		}
		case (4) :
		{
			if (Switch)
			{
				Keyboard->ActorState = false;
			}
			break;
		}
		default:
			break;
	}
	
}