// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LidarPointCloud.h"
#include "LidarPointCloudActor.h"
#include "LidarPointCloudShared.h"
#include "PointCloudActor.generated.h"

UCLASS()
class VRTELEOPERATION_API APointCloudActor : public ALidarPointCloudActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointCloudActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	class UROSIntegrationGameInstance* ROSInst;

	UPROPERTY()
	class UTopic* PointCloudTopic;

	struct data_float32
	{
		union {
			uint8_t d[4];
			float f;
		};
	};

	float scale = 100.0;

	/*
	TArray64<FLidarPointCloudPoint> points;
	*/

	UPROPERTY()
	TArray<FLidarPointCloudPoint> points;

	UPROPERTY()
	ULidarPointCloud* pointcloud;

	bool bNeedsUpdate;

};
