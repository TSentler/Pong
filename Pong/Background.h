// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Background.generated.h"

UCLASS()
class PONG_API ABackground : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackground(const FObjectInitializer& ObjectInitializer);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Set the Width of this sprite
	void SetWidth(float Width);

	// Set the Height of this sprite
	void SetHeight(float Height);

	// Set the Width and Height of this sprite via a FVector2D
	void SetDimensions(FVector2D& Dimensions);
	
	// Get the scale
	FVector& GetScale();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	class UPaperSpriteComponent* Sprite;


	
	
};
