// Fill out your copyright notice in the Description page of Project Settings.

#include "JustDoIT.h"
#include "JustDoITActor.h"
#include <Runtime/Engine/Public/Engine.h>


// Sets default values
AJustDoITActor::AJustDoITActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorState = true;
}

// Called when the game starts or when spawned
void AJustDoITActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJustDoITActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AJustDoITActor::OnStartPlayerLookAt_Implementation()
{
}

void AJustDoITActor::OnFinishPlayerLookAt_Implementation()
{
}

void AJustDoITActor::OnInteraction_Implementation(const int32& ProblemType)
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("INTERACT MADAFAKA"));
	//}

	//if (ActorState == false && (this->ProblemType == 0 || ProblemType == this->ProblemType))
	if (ActorState == false)
	{
		ActorState = true;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Computer repaired"));
		}
	}

}