// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ball.h"
#include "PongHUD.h"
#include "Paddle.h"
#include "GameFramework/GameState.h"
#include "PongGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	enum PONG_STATES
	{
		WAITING_TO_START,
		PUSH_BALL,
		PLAYING,
		RESET
	};
	
public:

	APongGameStateBase(const FObjectInitializer& ObjectInitializer);

	//Tick called every frame
	virtual void Tick(float DeltaTime) override;

	//Mutator for the reference to the Ball
	void SetBall(class ABall* lBall);
	
	//Overlap event for when the ball overlaps
	UFUNCTION()
	void BallOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	//bool b_StartGame = false;

protected:

	//Called when play begins
	virtual void BeginPlay() override;

private:
	//Helper function to Reset the Board to it's initial state
	void ResetBoard();
	//The current state the game is in
	PONG_STATES CurrentState;

	//Reference to the Ball
	class ABall* Ball;

	//booleans to keep track of when a goal is scored
	bool bAIScored;
	bool bPlayerScored;

	//values to store to the current score
	int AIScore = 0;
	int PlayerScore = 0;

	//Reference to the controller used for the paddle
	class APlayerController* Controller;
	class APongHUD* HUD;
};
