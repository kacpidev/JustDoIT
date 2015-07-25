// Fill out your copyright notice in the Description page of Project Settings.

#include "JustDoIT.h"
#include "JustDoITWorkplace.h"


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
}

bool AJustDoITWorkplace::IsWorking()
{
	if (Computer && CDROM && Wire && Switch)
	{
		return (Computer->ActorState && CDROM->ActorState && Wire->ActorState && Switch->ActorState);
	}

	return true;
}
