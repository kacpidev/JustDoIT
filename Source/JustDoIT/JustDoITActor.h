// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GameFramework/Actor.h"
#include "JustDoITActor.generated.h"

#define WORKING_FINE 0
#define IN_FIRE 1
#define NO_CABLE 2
#define PRINTER_PROBLEM 3
#define FUCKIN_MIRACLES 4

UCLASS()
class JUSTDOIT_API AJustDoITActor : public AActor {
	GENERATED_BODY ()

public:
	// Sets default values for this actor's properties
	AJustDoITActor ();

	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

	// Called every frame
	virtual void Tick (float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
		void OnInteraction(); 
	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
		void OnStartPlayerLookAt();
	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
		void OnFinishPlayerLookAt();


public:
	int ActorState;
	float CashTimer;

};
