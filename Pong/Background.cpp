// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Background.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABackground::ABackground( const FObjectInitializer& ObjectInitializer ):
	Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootBackground"));

	//Find the Background Sprite -- Right click on your sprite in the editor and click copy reference to get the path to it
	ConstructorHelpers::FObjectFinder<UPaperSprite>BackgroundSpriteRef(TEXT("PaperSprite'/Game/Sprites/Background.Background'"));

	//Create a default UPaperSpriteComponent and register it to this Actor
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComp"));

	//Set the Sprite to render for the UPaperSpriteComponent to the BackgroundSprite Reference we grabbed
	Sprite->SetSprite(BackgroundSpriteRef.Object);
}

// Called when the game starts or when spawned
void ABackground::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABackground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set the Width of this sprite
void ABackground::SetWidth(float Width)
{
	//calculate the new X scale value
	float sourceWidth = Sprite->GetSprite()->GetSourceSize().X;
	float scale;

	//Scale must be > 1 is the sourceWidth < Width and < 1 in the other case
	if (Width <= sourceWidth)
	{
		scale = sourceWidth / Width;
	}
	else
	{
		scale = Width / sourceWidth;
	}

	//Update the current scale with the new value
	FVector scaleV = Sprite->RelativeScale3D;
	scaleV.X = scale;
	Sprite->SetRelativeScale3D(scaleV);
}

// Set the Height of this sprite
void ABackground::SetHeight(float Height)
{
	//calculate the new Z scale value (Camera is orientated so that Z is up/down)
	float sourceHeight = Sprite->GetSprite()->GetSourceSize().Y;
	float scale;

	//Scale must be > 1 is the sourceHeight < Height and < 1 in the other case
	if (Height <= sourceHeight)
	{
		scale = sourceHeight / Height;
	}
	else
	{
		scale = Height / sourceHeight;
	}

	//Update the current scale with the new value
	FVector scaleV = Sprite->RelativeScale3D;
	scaleV.Z = scale;
	Sprite->SetRelativeScale3D(scaleV);
}

//Wrapper around SetHeight and SetWidth for a FVector2D
void ABackground::SetDimensions(FVector2D& Dimensions)
{
	SetWidth(Dimensions.X);
	SetHeight(Dimensions.Y);
}

FVector& ABackground::GetScale()
{
	return Sprite->RelativeScale3D;
}