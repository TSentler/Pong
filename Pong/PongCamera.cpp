// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "PongCamera.h"


APongCamera::APongCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootPawn"));
	MyCamera = GetCameraComponent();
	MyCamera->SetupAttachment(RootComponent);

	//Set the Camera To Orthographic.  Also set the Location and Rotation on the Camera: X is left and right, Z is up and down, Y is depth relative to this camera
	MyCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	MyCamera->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
	MyCamera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	MyCamera->SetAbsolute(true, true, true);

}

//Get the Dimensions of what our camera can view
FVector2D APongCamera::GetViewDimensions()
{
	FVector2D dimensions = FVector2D::ZeroVector;
	//The width is the Orthographic view Width.  Calculate the height from the Aspect ratio and OrthoWidth
	dimensions.X = MyCamera->OrthoWidth;
	dimensions.Y = 1 / (MyCamera->AspectRatio / MyCamera->OrthoWidth);

	return dimensions;
}

