// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Ball.h"

#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:	
	//Constructor where we set the default classes to initialize
	APongGameMode();

	//Function called to spawn our pawn objects into the world
	virtual void StartPlay() override;

	ABall* Ball;

};
