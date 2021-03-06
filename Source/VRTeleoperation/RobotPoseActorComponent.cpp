// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPoseActorComponent.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/geometry_msgs/Twist.h"

// Sets default values for this component's properties
URobotPoseActorComponent::URobotPoseActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URobotPoseActorComponent::BeginPlay()
{
	Super::BeginPlay();

	m_PoseTopic = NewObject<UTopic>(UTopic::StaticClass());
	ROSInst = Cast<UROSIntegrationGameInstance>(GetWorld()->GetGameInstance());

	if (ROSInst)
	{
		m_PoseTopic->Init(ROSInst->ROSIntegrationCore, TEXT("/cmd_vel"), TEXT("geometry_msgs/Twist"));

		std::function<void(TSharedPtr<FROSBaseMsg>)> PoseCallback = URobotPoseActorComponent::PoseCallbackImpl;
		m_PoseTopic->Subscribe(PoseCallback);
	}
	
}


// Called every frame
void URobotPoseActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URobotPoseActorComponent::PoseCallbackImpl(TSharedPtr<FROSBaseMsg> msg)
{
	auto Concrete = StaticCastSharedPtr<ROSMessages::geometry_msgs::Twist>(msg);
	if (Concrete.IsValid())
	{
		//UE_LOG(LogTemp, Log, TEXT("%s"), (*(Concrete->linear)));
	}

	return;
}

