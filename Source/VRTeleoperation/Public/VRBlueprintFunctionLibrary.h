// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VRBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VRTELEOPERATION_API UVRBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "VR Teleoperation")
	static void test();
};
