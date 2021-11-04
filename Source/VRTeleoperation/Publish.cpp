// Fill out your copyright notice in the Description page of Project Settings.


#include "Publish.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"

// Sets default values
APublish::APublish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APublish::BeginPlay()
{
	Super::BeginPlay();

	// Initialize a topic
	m_ExampleTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	m_ExampleTopic->Init(rosinst->ROSIntegrationCore, TEXT("/example_topic"), TEXT("std_msgs/String"));

	// (Optional) Advertise the topic
	m_ExampleTopic->Advertise();

	
}

// Called every frame
void APublish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Publish a string to the topic
	TSharedPtr<ROSMessages::std_msgs::String> StringMessage(new ROSMessages::std_msgs::String("This is an example"));
	if (m_ExampleTopic->Publish(StringMessage)) {
		UE_LOG(LogTemp, Log, TEXT("Publish."));
	}
	else {
		//UE_LOG(LogTemp, Log, TEXT("Could not publish."));
	}

}

