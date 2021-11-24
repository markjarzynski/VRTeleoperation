// Fill out your copyright notice in the Description page of Project Settings.


#include "OdometryActorComponent.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/nav_msgs/Odometry.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UOdometryActorComponent::UOdometryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOdometryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UTopic* OdometryTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* ROSInst = Cast<UROSIntegrationGameInstance>(GetWorld()->GetGameInstance());

	if (ROSInst)
	{
		OdometryTopic->Init(ROSInst->ROSIntegrationCore, TEXT("/odometry/filtered"), TEXT("nav_msgs/Odometry"));
		std::function<void(TSharedPtr<FROSBaseMsg>)> OdometryCallback = [&](TSharedPtr<FROSBaseMsg> msg) -> void
		{
			auto Concrete = StaticCastSharedPtr<ROSMessages::nav_msgs::Odometry>(msg);

			if (Concrete.IsValid())
			{
				ROSMessages::geometry_msgs::Pose pose = Concrete->pose.pose;

				UE_LOG(LogTemp, Log, TEXT("Odometry Callback %d %f %f %f"), count, pose.position.x, pose.position.y, pose.position.z);

				float scale = 10.0;

				FVector location = FVector(pose.position.x * scale, pose.position.y * scale, pose.position.z * scale);
				FQuat orientation = FQuat(pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w);
				FRotator rotation = orientation.Rotator();

				this->GetOwner()->SetActorLocationAndRotation(location, rotation);
			}
			return;
		};

		OdometryTopic->Subscribe(OdometryCallback);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("ROSInst not initalized. Is ROSBridge running?"));
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), *GetOwner()->GetName());

	count = 0;

}


// Called every frame
void UOdometryActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*
void UOdometryActorComponent::OdometryCallback(TSharedPtr<class FROSBaseMsg> msg)
{
	auto Concrete = StaticCastSharedPtr<ROSMessages::nav_msgs::Odometry>(msg);

	if (Concrete.IsValid())
	{
		ROSMessages::geometry_msgs::Pose pose = Concrete->pose.pose;

		UE_LOG(LogTemp, Log, TEXT("Odometry Callback %d %f %f %f"), count, pose.position.x, pose.position.y, pose.position.z);

		FVector location = FVector(pose.position.x, pose.position.y, pose.position.z);
		FRotator rotation = FRotator();

		count++;
	}
}
*/