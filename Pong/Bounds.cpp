// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Bounds.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"


// Sets default values
ABounds::ABounds(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootBounds"));
	//Find the Bounds Sprite -- Right click on your sprite in the editor and click copy reference to get the path to it
	ConstructorHelpers::FObjectFinder<UPaperSprite> BoundsSpriteRef(TEXT("PaperSprite'/Game/Sprites/Bounds.Bounds'"));

	//Create a default UPaperSpriteComponent and register it to this Actor
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComp"));

	//Set the Sprite to render for the UPaperSpriteComponent to the BoundsSprite Reference we grabbed
	Sprite->SetSprite(BoundsSpriteRef.Object);

	//Make sure that this component blocks everything
	Sprite->GetBodyInstance()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sprite->GetBodyInstance()->SetObjectType(ECollisionChannel::ECC_WorldStatic);

	//Don't draw this sprite
	Sprite->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABounds::BeginPlay()
{
	Super::BeginPlay();
	//Set the location of the Bounds to be the same as the paddle - This is just hardcoded to 50 units
	Sprite->SetRelativeLocation(FVector(0.0f, 50.f, 0.0f));
	Sprite->SetAbsolute(true, true, true);

	//Ensure that this component's name is "Bounds"
	Rename(TEXT("Bounds"));
}

// Called every frame
void ABounds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set the X,Y, and Z scale for the sprite
void ABounds::SetScale(FVector& vector)
{
	Sprite->SetRelativeScale3D(vector);
}