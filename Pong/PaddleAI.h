// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "PaddleAI.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APaddleAI : public APaddle
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	APaddleAI(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Ball Reference
	void SetBall(ABall* Ball);

	// AI Paddle Reset override
	virtual void Reset() override;

private:

	//Reference to Ball
	ABall* Ball;
	
	
};
