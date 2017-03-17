// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

UCLASS()
class PONG_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddle(const FObjectInitializer& ObjectInitializer);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Function called to move the paddle.  Scale represents up/down
	void MovePaddle(float Scale);

	// Notification when the paddle begins to overlap another Actor
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Notification when the paddle ends overlap
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// How fast the paddle is moving up or down
	float GetZVelocity();

	// Get the location of the sprite
	FVector2D GetPosition();

	// Reset the paddles location
	virtual void Reset();

	// Sets if the paddle can be moved
	void SetMoveable(bool bMoveable);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paddle)
	class UPaperSpriteComponent* Sprite;

	//Booleans for keeping track of valid movement directions
	bool bMoveUp;
	bool bMoveDown;

private:
	FVector CurrentVelocity;

	//How fast the paddle is moving
	float Velocity;

	//Is the paddle moveable, can it move?
	bool bMoveable;

};
