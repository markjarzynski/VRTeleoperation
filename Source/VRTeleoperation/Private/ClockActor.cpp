// Fill out your copyright notice in the Description page of Project Settings.


#include "ClockActor.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/ROSTime.h"
#include "ROSIntegration/Public/rosgraph_msgs/Clock.h"

// Sets default values
AClockActor::AClockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClockActor::BeginPlay()
{
	Super::BeginPlay();
	FROSTime originalTime = FROSTime::Now();

	// Make sure our system clock keeps clicking along
	FROSTime::SetUseSimTime(false);
	FWorldDelegates::OnWorldTickStart.AddUObject(this, &AClockActor::OnWorldTickStart);

	UROSIntegrationGameInstance* ROSInst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	ClockTopic = NewObject<UTopic>(UTopic::StaticClass());
	ClockTopic->Init(ROSInst->ROSIntegrationCore, FString(TEXT("/clock")), FString(TEXT("rosgraph_msgs/Clock")), 3);

	ClockTopic->Advertise();
}

void AClockActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Log, TEXT("AClockActor::EndPlay()"));

	ClockTopic->Unadvertise();

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AClockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClockActor::OnWorldTickStart(UWorld* world, ELevelTick TickType, float DeltaTime)
{
	// Make sure we only care about the LEVELTICK_TimeOnly since we are updating time 
	if (bSimulateTime && TickType == ELevelTick::LEVELTICK_TimeOnly)
	{
		FApp::SetFixedDeltaTime(FixedUpdateInterval);
		FApp::SetUseFixedTimeStep(bUseFixedUpdateInterval);

		FROSTime now = FROSTime::Now();

		// send /clock topic to let everyone know what time it is...
		TSharedPtr<ROSMessages::rosgraph_msgs::Clock> ClockMessage(new ROSMessages::rosgraph_msgs::Clock(now));
		ClockTopic->Publish(ClockMessage);
	}
}
