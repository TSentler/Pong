// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "PongCamera.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:

	APongCamera(const FObjectInitializer& ObjectInitializer);

	//Get a 2D vector representing the Height/Width of what is being current displayed on the screen
	FVector2D GetViewDimensions();
private:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* MyCamera;
	
};
