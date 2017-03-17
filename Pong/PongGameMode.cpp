// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "PongGameMode.h"
#include "Paddle.h"
#include "PongCamera.h"
#include "Background.h"
#include "Ball.h"
#include "Bounds.h"
#include "Goal.h"
#include "PongGameStateBase.h"
#include "PaddleAI.h"
#include "PongHUD.h"

//const float Y_GAME_POSITION = 50.f;

APongGameMode::APongGameMode()
{
	DefaultPawnClass = APaddle::StaticClass();
	GameStateClass = APongGameStateBase::StaticClass();
	HUDClass = APongHUD::StaticClass();
	//GameStateClass = APongGameState2::StaticClass();
}


void APongGameMode::StartPlay()
{
	Super::StartPlay();
	UWorld* const World = GetWorld();
	if (World)
	{
		//Spawn the Ball into the World
		Ball = World->SpawnActor<ABall>(ABall::StaticClass());

		APongGameStateBase* gameState = GetGameState<APongGameStateBase>();
		gameState->SetBall(Ball);
		

		APongCamera* camera = World->SpawnActor<APongCamera>(APongCamera::StaticClass());

		//Camera is set to the CameraActor created
		World->GetFirstPlayerController()->SetViewTarget(camera);

		//Set the background to fill up the entire view of the camera
		ABackground* background = World->SpawnActor<ABackground>(ABackground::StaticClass());
		FVector2D dimensions = camera->GetViewDimensions();
		background->SetDimensions(dimensions);

		FVector scale = background->GetScale();
		//Spawn the Bounds into the World
		ABounds* bounds = World->SpawnActor<ABounds>(ABounds::StaticClass());
		bounds->SetScale(scale);


		//Get a reference to the paddles and rename them
		APaddle* playerPaddle = (APaddle*)World->GetFirstPlayerController()->GetPawn();
		playerPaddle->Rename(TEXT("PlayerPaddle"));
		
		//Spawn the Player and AI Goals
		AGoal* playerGoal = World->SpawnActor<AGoal>(AGoal::StaticClass());
		playerGoal->SetScale(scale);
		playerGoal->Rename(TEXT("PlayerGoal"));

		//playerGoal spawns on the left, aiGoal on the right
		FVector playerPos;
		playerPos.X = playerPaddle->GetPosition().X - (playerGoal->GetWidth() * scale.X) / 2;
		playerPos.Y = 50.f;
		playerPos.Z = 0.f;
		playerGoal->SetPosition(playerPos);

		APaddleAI* aiPaddle = World->SpawnActor<APaddleAI>(APaddleAI::StaticClass());

		aiPaddle->Rename(TEXT("AIPaddle"));
		aiPaddle->SetBall(Ball);

		AGoal* aiGoal = World->SpawnActor<AGoal>(AGoal::StaticClass());
		aiGoal->SetScale(scale);
		aiGoal->Rename(TEXT("AIGoal"));

		FVector aiPos;
		aiPos.X = 5.0f + aiPaddle->GetPosition().X + (playerGoal->GetWidth() * scale.X) / 2;
		aiPos.Y = 50.f;
		aiPos.Z = 0.f;
		aiGoal->SetPosition(aiPos);

	}
}

