// Fill out your copyright notice in the Description page of Project Settings.


#include "Echo.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"

// Sets default values
AEcho::AEcho()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEcho::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Echo BeginPlay"));

	// Initialize a topic
	m_ExampleTopic = NewObject<UTopic>(UTopic::StaticClass());
	ROSInst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	if (ROSInst)
	{
		m_ExampleTopic->Init(ROSInst->ROSIntegrationCore, TEXT("/example_topic"), TEXT("std_msgs/String"));

		std::function<void(TSharedPtr<FROSBaseMsg>)> EchoCallback = AEcho::EchoCallbackImpl;
		m_ExampleTopic->Subscribe(EchoCallback);

		UE_LOG(LogTemp, Warning, TEXT("Echo Subscribe"));
	}
}

void AEcho::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UE_LOG(LogTemp, Warning, TEXT("Echo EndPlay"));
}

// Called every frame
void AEcho::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEcho::EchoCallbackImpl(TSharedPtr<FROSBaseMsg> msg)
{
	UE_LOG(LogTemp, Warning, TEXT("Echo"));
	auto Concrete = StaticCastSharedPtr<ROSMessages::std_msgs::String>(msg);
	if (Concrete.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), (*(Concrete->_Data)));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not valid."));
	}

	return;
}

