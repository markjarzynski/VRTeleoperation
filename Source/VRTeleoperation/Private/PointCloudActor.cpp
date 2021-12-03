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

	
	// Fix for Error: Provided bounds are incorrect
	/*
	FLidarPointCloudPoint p[2];
	p[0] = FLidarPointCloudPoint(FVector(0, 0, 50), FColor::White, false, 0);
	p[1] = FLidarPointCloudPoint(FVector(0, 0, -50), FColor::White, false, 0);
	*/
	//points.Add(FLidarPointCloudPoint(FVector(0, 0, 50), FColor::White, false, 0));
	//points.Add(FLidarPointCloudPoint(FVector(0, 0, -50), FColor::White, false, 0));
	//pointcloud->InsertPoint(FLidarPointCloudPoint(FVector(0, 0, 50), FColor::White, false, 0), GetDefault<ULidarPointCloudSettings>()->DuplicateHandling, true, FVector(0, 0, 0));
	//pointcloud->InsertPoint(FLidarPointCloudPoint(FVector(0, 0, -50), FColor::White, false, 0), GetDefault<ULidarPointCloudSettings>()->DuplicateHandling, true, FVector(0, 0, 0));

	/*
	FBox BoundingBox = ULidarPointCloud::CalculateBoundsFromPoints(p, 2);
	pointcloud = ULidarPointCloud::Initialize(BoundingBox);
	*/

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

				//UE_LOG(LogTemp, Log, TEXT("PointCloud: %d %d, point_step: %d"), height, width, point_step);

				TArray<FLidarPointCloudPoint> points;
				points.Reserve(num_points);

				for (uint32 i = 0; i < num_points; i += point_step) {

					data_float32 x, y, z, rgb;

					for (int j = 0; j < 4; j++) {
						x.d[j] = Concrete->data_ptr[i + j];
					}

					for (int j = 0; j < 4; j++) {
						y.d[j] = Concrete->data_ptr[i + 4 + j];
					}

					for (int j = 0; j < 4; j++) {
						z.d[j] = Concrete->data_ptr[i + 8 +j];
					}

					for (int j = 0; j < 4; j++) {
						rgb.d[j] = Concrete->data_ptr[i + 16 + j];
					}

					//UE_LOG(LogTemp, Log, TEXT("Data: %d %d %d %d"), Concrete->data_ptr[i], Concrete->data_ptr[i + 1], Concrete->data_ptr[i + 2], Concrete->data_ptr[i + 3]);
					

					if (!isnan(x.f) && !isnan(y.f) && !isnan(z.f)) {
						if (true /*abs(x.f) < 10000 && abs(y.f) < 10000 && abs(z.f) < 10000*/) {
							const FVector p = FVector(-x.f * scale, z.f * scale, -y.f * scale);
							points.Emplace(p);
							//UE_LOG(LogTemp, Log, TEXT("Point: %f %f %f %f"), x.f, y.f, z.f, rgb.f);

							//pointcloud->InsertPoint(p, GetDefault<ULidarPointCloudSettings>()->DuplicateHandling, true, FVector(0, 0, 0));
						}
					}

				}

				if (points.Num() > 0 && GetPointCloud() == nullptr) {
					// Fix for Error: Provided bounds are incorrect
					points.Add(FLidarPointCloudPoint(FVector(0, 0, 50), FColor::White, false, 0));
					points.Add(FLidarPointCloudPoint(FVector(0, 0, -50), FColor::White, false, 0));

					this->pointcloud = ULidarPointCloud::CreateFromData(points, false);

					//if (GetPointCloud()->GetNumPoints() == 0) {
					SetPointCloud(pointcloud);
					//}
				} else {
					//GetPointCloud()->Initialize(FBox());
					GetPointCloud()->InsertPoints(points, ELidarPointCloudDuplicateHandling::Ignore, true, FVector(0, 0, 0));
				}

				//pointcloud->InsertPoints(points, GetDefault<ULidarPointCloudSettings>()->DuplicateHandling, true, FVector(0, 0, 0));

				//UE_LOG(LogTemp, Log, TEXT("Num Points: %d"), points.Num());

				

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

	/*
	if (points.Num() > 0) {
		pointcloud = ULidarPointCloud::CreateFromData(points, false);
		SetPointCloud(pointcloud);
		//points.Empty();
	}
	*/

}

