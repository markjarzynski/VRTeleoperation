// Fill out your copyright notice in the Description page of Project Settings.


#include "VRBlueprintFunctionLibrary.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/geometry_msgs/Twist.h"

void UVRBlueprintFunctionLibrary::test()
{
	UE_LOG(LogTemp, Log, TEXT("Test"));
	
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

void UVRBlueprintFunctionLibrary::joy_teleop(UObject* WorldContextObject, float x, float y)
{
	UE_LOG(LogTemp, Log, TEXT("joy_teleop: %f, %f"), x, y);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);

	class UTopic* JoyTeleopTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(World->GetGameInstance());
	JoyTeleopTopic->Init(rosinst->ROSIntegrationCore, TEXT("/joy_teleop/cmd_vel"), TEXT("geometry_msgs/Twist"));

	ROSMessages::geometry_msgs::Twist* twist = new ROSMessages::geometry_msgs::Twist();

	twist->linear = ROSMessages::geometry_msgs::Vector3(y, 0.0, 0.0);
	twist->angular = ROSMessages::geometry_msgs::Vector3(0.0, 0.0, -x);

	TSharedPtr<ROSMessages::geometry_msgs::Twist> TwistMessage(twist);
	JoyTeleopTopic->Publish(TwistMessage);

}