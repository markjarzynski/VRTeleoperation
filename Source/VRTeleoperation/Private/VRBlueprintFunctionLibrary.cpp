// Fill out your copyright notice in the Description page of Project Settings.


#include "VRBlueprintFunctionLibrary.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"

void UVRBlueprintFunctionLibrary::test()
{
	/*
	// Initialize a topic
	UTopic* ExampleTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetWorld()->GetGameInstance());
	ExampleTopic->Init(rosinst->ROSIntegrationCore, TEXT("/example_topic"), TEXT("std_msgs/String"));

	// Publish a string to the topic
	TSharedPtr<ROSMessages::std_msgs::String> StringMessage(new ROSMessages::std_msgs::String("This is an example"));
	ExampleTopic->Publish(StringMessage);
	*/
}