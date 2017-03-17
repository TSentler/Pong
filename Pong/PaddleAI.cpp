// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "PaddleAI.h"
#include "Ball.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
APaddleAI::APaddleAI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	
	
	//RootComponent = pRoot;
}

// Called when the game starts or when spawned
void APaddleAI::BeginPlay()
{
	Super::BeginPlay();
	Sprite->SetRelativeLocation(FVector(200.0f, 50.f, 0.0f));
	Sprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void APaddleAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Paddle AI can always move
	bMoveUp = true;
	bMoveDown = true;

	if (Ball != NULL)
	{
		// Update the direction the AI should move based on where the Ball is
		if (Sprite->GetComponentLocation().Z > Ball->GetActorLocation().Z)
		{
			MovePaddle(-1.0f);
		}
		else if (Sprite->GetComponentLocation().Z < Ball->GetActorLocation().Z)
		{
			MovePaddle(1.0f);
		}
		else
		{
			MovePaddle(0.0f);
		}
	}

}

void APaddleAI::SetBall(ABall* lBall)
{
	Ball = lBall;
}

// Reset the paddles location
void APaddleAI::Reset()
{
	Sprite->SetRelativeLocation(FVector(200.0f, 50.f, 0.0f));
	Sprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	bMoveUp = true;
	bMoveDown = true;
}