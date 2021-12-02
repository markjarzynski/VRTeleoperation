// Fill out your copyright notice in the Description page of Project Settings.


#include "PointCloudActor.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/sensor_msgs/PointCloud2.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
APointCloudActor::APointCloudActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APointCloudActor::BeginPlay()
{
	Super::BeginPlay();

	PointCloudTopic = NewObject<UTopic>(UTopic::StaticClass());
	ROSInst = Cast<UROSIntegrationGameInstance>(GetWorld()->GetGameInstance());

	if (ROSInst)
	{
		PointCloudTopic->Init(ROSInst->ROSIntegrationCore, TEXT("/camera/depth/points"), TEXT("sensor_msgs/PointCloud2"));
		std::function<void(TSharedPtr<FROSBaseMsg>)> PointCloudCallback = [&](TSharedPtr<FROSBaseMsg> msg) -> void
		{
			auto Concrete = StaticCastSharedPtr<ROSMessages::sensor_msgs::PointCloud2>(msg);

			if (Concrete.IsValid())
			{
				//ROSMessages::sensor_msgs::PointCloud2::height
				uint32 height = Concrete->height;
				uint32 width = Concrete->width;
				uint32 num_points = Concrete->row_step * Concrete->height;
				uint32 point_step = Concrete->point_step;

				UE_LOG(LogTemp, Log, TEXT("PointCloud: %d %d"), height, width);

				for (uint32 i = 0; i < num_points; i += point_step) {

					data_float32 x, y, z, rgb;

					for (int j = 0; j < 4; j++) {
						x.d[j] = Concrete->data_ptr[i + 3 - j];
					}

					for (int j = 4; j < 4; j++) {
						y.d[j] = Concrete->data_ptr[i + 3 - j];
					}

					for (int j = 8; j < 4; j++) {
						z.d[j] = Concrete->data_ptr[i + 3 - j];
					}

					for (int j = 16; j < 4; j++) {
						rgb.d[j] = Concrete->data_ptr[i + 3 - j];
					}
					
					FVector p = FVector(x.f, y.f, z.f);

					//UE_LOG(LogTemp, Log, TEXT("Point: %f %f %f %f"), x.f, y.f, z.f, rgb.f);
				}



				Concrete->data_ptr;

				ULidarPointCloud* pc = this->GetPointCloud();

				//UE_LOG(LogTemp, Log, TEXT("Odometry Callback %f %f %f"), pose.position.x, pose.position.y, pose.position.z);
			}
			return;
		};

		PointCloudTopic->Subscribe(PointCloudCallback);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("ROSInst not initalized. Is ROSBridge running?"));
	}
}

// Called every frame
void APointCloudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

