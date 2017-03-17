// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Paddle.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
APaddle::APaddle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set this pawn to be controlled by the lowest-numbered player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	USceneComponent* rootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootPawn"));

	RootComponent = rootSceneComponent;
	
	//Find the Paddle Sprite -- Right click on your sprite in the editor and click copy reference to get the path to it
	ConstructorHelpers::FObjectFinder<UPaperSprite> PaddleSpriteRef(TEXT("PaperSprite'/Game/Sprites/Paddle.Paddle'"));
	//Create a default UPaperSpriteComponent and register it to this Actor
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComp"));
	//Set the Sprite to render for the UPaperSpriteComponent to the PaddleSprite Reference we grabbed
	Sprite->SetSprite(PaddleSpriteRef.Object);
	//Sprite->SetupAttachment(rootSceneComponent);
	//RootComponent = Sprite;

	ObjectInitializer.CreateDefaultSubobject<UPawnMovementComponent>(this, TEXT("MovementComp"));

	//Can initially move in all directions
	bMoveUp = true;
	bMoveDown = true;

	//Set the sprite to generate overlap events for world-static objects -> The Bounds is set to World Static, so this should generate an overlap event now
	Sprite->GetBodyInstance()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sprite->GetBodyInstance()->SetObjectType(ECollisionChannel::ECC_Pawn);
	Sprite->GetBodyInstance()->SetResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);

	Sprite->SetSimulatePhysics(false);

	//Set the location of the Paddle to the Left
	Sprite->SetRelativeLocation(FVector(-200.0f, 50.f, 0.0f));
	Sprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	Sprite->SetRelativeScale3D(FVector(0.1f, 1.0f, 0.1f));
	Sprite->SetAbsolute(true, true, true);	

}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	Sprite->SetRelativeLocation(FVector(-200.0f, 50.f, 0.0f));
	Sprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	//Ensure that this component's name is "Paddle"
	//Rename(TEXT("Paddle"));
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		//FString s = FString::SanitizeFloat(CurrentVelocity.Z);

	if ((bMoveUp && CurrentVelocity.Z > 0) || (bMoveDown && CurrentVelocity.Z < 0))
	{

		FVector NewLocation = Sprite->GetComponentLocation() + (CurrentVelocity * DeltaTime);
		Sprite->SetRelativeLocation(NewLocation);
	}
	// Update the sprites location based on the movement input
	//FVector move = GetMovementInputVector();
	//FVector location = GetActorLocation();
	//location += move*DeltaTime;
	//Sprite->SetRelativeLocation(location);
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	// Bind the axis - if we press up, the function is called with 1.0.  if we press down, the function is called with -1.0.
	// if we do nothing, the function is called with 0.0f
	InputComponent->BindAxis("Move", this, &APaddle::MovePaddle);

	//Velocity = 0.0f;
}

void APaddle::MovePaddle(float Scale)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Z = FMath::Clamp(Scale, -1.0f, 1.0f) * 100.0f;
	Velocity = Scale * 75.0f;
}


void APaddle::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->GetName().Equals("Bounds"))
	{
		//If moving into a bound, set the movement in that direction to false
		if (CurrentVelocity.Z > 0.0f)
		{
			bMoveUp = false;
		}
		else if (CurrentVelocity.Z < 0.0f)
		{
			bMoveDown = false;
		}

	}
}

void APaddle::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->GetName().Equals("Bounds"))
	{
		//Out of the bounds so enable all movement inputs
		bMoveUp = true;
		bMoveDown = true;
	}
}

float APaddle::GetZVelocity()
{
	return Velocity;
}

FVector2D APaddle::GetPosition()
{
	FVector2D location;
	location.X = Sprite->GetComponentLocation().X;
	location.Y = Sprite->GetComponentLocation().Z;

	return location;
}

// Reset the paddles location
void APaddle::Reset()
{
	Sprite->SetRelativeLocation(FVector(-200.0f, 50.f, 0.0f));
	Sprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	Sprite->SetRelativeScale3D(FVector(0.1f, 1.0f, 0.1f));
	bMoveUp = true;
	bMoveDown = true;
}

void APaddle::SetMoveable(bool lbMoveable)
{
	this->bMoveable = lbMoveable;
}
//FString s = FString::FromInt(locationPreviousPart.X);
//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);