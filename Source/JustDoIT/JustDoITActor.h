// Fill out your copyright notice in the Description page of Project Settings.
#pragma once



#include "GameFramework/Actor.h"
#include "JustDoITActor.generated.h"

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
		void OnInteraction(const int32& ProblemType); 
	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
		void OnStartPlayerLookAt();
	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
		void OnFinishPlayerLookAt();


public:
	UPROPERTY(BlueprintReadWrite)
	bool ActorState;
	UPROPERTY(BlueprintReadWrite)
	int32 ProblemType;
};
