// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Ball.h"
#include "PongHUD.h"
#include "Paddle.h"
#include "PongGameStateBase.h"

//bool b_StartGame = false;

APongGameStateBase::APongGameStateBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	CurrentState(PONG_STATES::WAITING_TO_START)
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void APongGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	HUD = (APongHUD*)Controller->GetHUD();
}

void APongGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If match is in progress, run the custom state machine
	UWorld* const World = GetWorld();
	//if (IsMatchInProgress())
	//{

		switch (CurrentState)
		{
		case PONG_STATES::RESET:
			ResetBoard();
			for (auto it = GetWorld()->GetPawnIterator(); it.GetIndex() < GetWorld()->GetNumPawns(); it++)
			{
				((APaddle*)it->Get())->SetMoveable(false);
			}
			CurrentState = PONG_STATES::WAITING_TO_START;
			break;

		case PONG_STATES::WAITING_TO_START:
			HUD->DisplayWaitingForSpace(true);
			if (Controller->WasInputKeyJustReleased(EKeys::SpaceBar))
			{
				HUD->DisplayWaitingForSpace(false);
				for (auto it = GetWorld()->GetPawnIterator(); it.GetIndex() < GetWorld()->GetNumPawns(); it++)
				{
					((APaddle*)it->Get())->SetMoveable(true);
				}
				CurrentState = PONG_STATES::PUSH_BALL;
			}
			break;

		case PONG_STATES::PUSH_BALL:
			if (Ball != NULL)
			{
				Ball->StartMove();//!!!!!!!!!!!!!!!!!!!!!!!!!!
				CurrentState = PONG_STATES::PLAYING;
			}
			break;

		case PONG_STATES::PLAYING:
			if (bPlayerScored || bAIScored)
			{
				HUD->SetScore(PlayerScore, AIScore);
				CurrentState = PONG_STATES::RESET;
			}
			break;

		default:
			CurrentState = PONG_STATES::RESET;
			break;
		}
	//}
}

void APongGameStateBase::SetBall(class ABall* lBall)
{
	Ball = lBall;
	Ball->OnActorBeginOverlap.AddDynamic(this, &APongGameStateBase::BallOverlap);
}

void APongGameStateBase::BallOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (OtherActor->GetName().Equals("PlayerGoal"))
	{
		bAIScored = true;
		AIScore++;
	}

	if (OtherActor->GetName().Equals("AIGoal"))
	{
		bPlayerScored = true;
		PlayerScore++;
	}
}

void APongGameStateBase::ResetBoard()
{
	bPlayerScored = false;
	bAIScored = false;
	// Reset the paddles
	for (auto it = GetWorld()->GetPawnIterator(); it.GetIndex() < GetWorld()->GetNumPawns(); it++)
	{
		((APaddle*)it->Get())->Reset();
	}

	Ball->Reset();
}
