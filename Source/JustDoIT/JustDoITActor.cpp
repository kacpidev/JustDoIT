// Fill out your copyright notice in the Description page of Project Settings.

#include "JustDoIT.h"
#include "JustDoITActor.h"


// Sets default values
AJustDoITActor::AJustDoITActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorState = 0;
	CashTimer = 0.f;
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
	float Money = -1.f;

	switch (ActorState) {
		case WORKING_FINE:
		{
			// generate dollar and $++ event
			CashTimer += DeltaTime;
			if (CashTimer >= 1.f) 
			{
				CashTimer = 0;
				Money = 1.f;
				//create event for manager;
				// spawn dollar
			}
			break;
		}

		// any other problem generates problem icon
		case IN_FIRE:
		{
			// 
			break;
		}
		case NO_CABLE:
		{
			break;
		}
		case PRINTER_PROBLEM:
		{
			break;
		}

		case FUCKIN_MIRACLES:
		{
			break;
		}
		default:
		{
			break;
		}

		// corporation.earnsomemoney(money);
	}
}

void JustDoItActor::OnInteraction () {
	//TODO

}