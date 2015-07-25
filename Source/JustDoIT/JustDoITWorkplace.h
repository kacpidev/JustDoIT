// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "JustDoITActor.h"
#include "JustDoITWorkplace.generated.h"

UCLASS()
class JUSTDOIT_API AJustDoITWorkplace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJustDoITWorkplace();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool IsWorking();
	
public:
	UPROPERTY()
		int32 ActorState;

	UPROPERTY(BlueprintReadWrite)
		AJustDoITActor* Computer;

	UPROPERTY(BlueprintReadWrite)
		AJustDoITActor* CDROM;

	UPROPERTY(BlueprintReadWrite)
		AJustDoITActor* Wire;

	UPROPERTY(BlueprintReadWrite)
		AJustDoITActor* Switch;
};
