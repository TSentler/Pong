// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PongHUD.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	APongHUD(const FObjectInitializer& ObjectInitializer);

	virtual void DrawHUD() override;

	//Display the current Pong Score on the screen
	void DisplayScore();

	//Display The text waiting for space
	void DisplaySpaceText();

	//Set if the waiting for space text should be displayed
	void DisplayWaitingForSpace(bool bSpace);

	//Set the score to be displayed
	void SetScore(int PlayerScore, int AIScore);

private:

	//The score of the game
	int Score[2];

	//Display space text?
	bool bWaitingForSpace;
	
	
};
