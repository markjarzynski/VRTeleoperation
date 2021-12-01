// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OdometryActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRTELEOPERATION_API UOdometryActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOdometryActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	float scale = 100.0;

	FVector location;
	FRotator rotation;


	UPROPERTY()
	class UROSIntegrationGameInstance* ROSInst;

	UPROPERTY()
	class UTopic* OdometryTopic;

	//static void OdometryCallback(TSharedPtr<class FROSBaseMsg> msg);
	
};
