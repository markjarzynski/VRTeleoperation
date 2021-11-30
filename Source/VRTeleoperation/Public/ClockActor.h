// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClockActor.generated.h"

UCLASS()
class VRTELEOPERATION_API AClockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClockActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void OnWorldTickStart(UWorld* world, ELevelTick TickType, float DeltaTime);

private:

	UPROPERTY()
	class UTopic* ClockTopic;

public:

	UPROPERTY(EditAnywhere)
	bool bSimulateTime;

	UPROPERTY(EditAnywhere)
	double FixedUpdateInterval;

	UPROPERTY(EditAnywhere)
	bool bUseFixedUpdateInterval;

};
