// Fill out your copyright notice in the Description page of Project Settings.


#include "Echo.h"

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

	UE_LOG(LogTemp, Warning, TEXT("Echo"));

	UTopic* m_topic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	m_topic->Init(rosinst->ROSIntegrationCore, TEXT("/example_topic"), TEXT("std_msgs/String"));

	// Create a std::function callback object
	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = [](TSharedPtr<FROSBaseMsg> msg) -> void
	{
		auto Concrete = StaticCastSharedPtr<ROSMessages::std_msgs::String>(msg);
		if (Concrete.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("Incoming string was: %s"), (*(Concrete->_Data)));
		}
		return;
	};

	// Subscribe to the topic
	m_topic->Subscribe(SubscribeCallback);
	
}

// Called every frame
void AEcho::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

