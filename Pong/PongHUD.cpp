// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "PongHUD.h"

APongHUD::APongHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Score[0] = 0;
	Score[1] = 0;
	bWaitingForSpace = false;
}


void APongHUD::DrawHUD()
{
	Super::DrawHUD();

	DisplayScore();

	if (bWaitingForSpace)
	{
		DisplaySpaceText();
	}
}

void APongHUD::DisplaySpaceText()
{
	FVector2D sLoc;
	GetOwningPlayerController()->ProjectWorldLocationToScreen(FVector(-50.0f, 0.0f, 0.0f), sLoc);
	FString s = "Press Space to Begin.";
	DrawText(s, FLinearColor::Blue, sLoc.X, sLoc.Y);
}

void APongHUD::DisplayScore()
{

	FVector2D sLoc;
	GetOwningPlayerController()->ProjectWorldLocationToScreen(FVector(-50.0f, 0.0f, 130.0f), sLoc);
	FString s = "Score: " + FString::FromInt(Score[0]) + " - " + FString::FromInt(Score[1]);
	DrawText(s, FLinearColor::Blue, sLoc.X, sLoc.Y);
}

void APongHUD::SetScore(int PlayerScore, int AIScore)
{
	Score[0] = PlayerScore;
	Score[1] = AIScore;
}

void APongHUD::DisplayWaitingForSpace(bool bSpace)
{
	bWaitingForSpace = bSpace;
}