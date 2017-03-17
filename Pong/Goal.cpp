// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Goal.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"


// Sets default values
AGoal::AGoal(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Find the Goal Sprite -- Right click on your sprite in the editor and click copy reference to get the path to it
	ConstructorHelpers::FObjectFinder<UPaperSprite> GoalSpriteRef(TEXT("PaperSprite'/Game/Sprites/Goal.Goal'"));

	//Create a default UPaperSpriteComponent and register it to this Actor
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComp"));

	//Set the Sprite to render for the UPaperSpriteComponent to the GoalSprite Reference we grabbed
	Sprite->SetSprite(GoalSpriteRef.Object);

	RootComponent = Sprite;

	//Make sure that this component overlaps
	Sprite->GetBodyInstance()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sprite->GetBodyInstance()->SetObjectType(ECollisionChannel::ECC_WorldStatic);
	Sprite->GetBodyInstance()->SetResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Sprite->SetVisibility(false);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set the X,Y, and Z scale for the sprite
void AGoal::SetScale(FVector& vector)
{
	Sprite->SetRelativeScale3D(vector);
}

void AGoal::SetPosition(FVector& position)
{
	Sprite->SetRelativeLocation(position);
}

float AGoal::GetWidth()
{
	return Sprite->GetSprite()->GetSourceSize().X;
}