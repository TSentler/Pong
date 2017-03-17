// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Ball.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Paddle.h"

// Sets default values
ABall::ABall(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//USceneComponent* rootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootPawn"));

	//RootComponent = rootSceneComponent;
	//Find the Ball Sprite -- Right click on your sprite in the editor and click copy reference to get the path to it
	ConstructorHelpers::FObjectFinder<UPaperSprite> BallSpriteRef(TEXT("PaperSprite'/Game/Sprites/Ball.Ball'"));

	//Create a default UPaperSpriteComponent and register it to this Actor
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("SpriteComp"));

	//Set the Sprite to render for the UPaperSpriteComponent to the BallSprite Reference we grabbed
	Sprite->SetSprite(BallSpriteRef.Object);

	RootComponent = Sprite;

	//Set the physics properties
	//Restrict the translation/rotation axis
	SetActorEnableCollision(true);
	Sprite->SetEnableGravity(false);
	Sprite->SetConstraintMode(EDOFMode::SixDOF);
	Sprite->GetBodyInstance()->bLockXRotation = true;
	Sprite->GetBodyInstance()->bLockYRotation = true;
	Sprite->GetBodyInstance()->bLockZRotation = true;
	Sprite->GetBodyInstance()->bLockXTranslation = false;
	Sprite->GetBodyInstance()->bLockYTranslation = true;
	Sprite->GetBodyInstance()->bLockZTranslation = false;

	//Enable Hit Notifies
	Sprite->SetNotifyRigidBodyCollision(true);

	//Set the ball to spawn in the middle of the Board and scale its size down
	Sprite->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	Sprite->SetRelativeScale3D(FVector(0.07f, 1.0f, 0.07f));
	Sprite->SetAbsolute(true, true, true);

	Sprite->SetLinearDamping(0.0f);
	Sprite->SetSimulatePhysics(true);

	Direction = FVector(0.0f, 0.0f, 0.0f);
	Velocity = 0.0f;
	
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set a time variable to be < one hundreth of a second
	float time = (DeltaTime > 0.01f ? 0.0083f : DeltaTime);

	//Update the translation based on the time variable
	FTransform transform = Sprite->GetRelativeTransform();
	transform.AddToTranslation(Direction * Velocity * time);
	Sprite->SetRelativeTransform(transform);
}

void ABall::StartMove()
{
	// Move the ball via setting the Direction and Velocity
	Direction = FVector(-1.0f, 0.0f, 0.0f);
	Velocity = 250.0f;
}

void ABall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	//Make sure that the physics velocities are set to 0.  We are keeping track of direction/speed.  We want this hit event so that we can easily mirror the direction
	Sprite->SetAllPhysicsAngularVelocity(FVector(0.0f, 0.0f, 0.0f));
	Sprite->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));

	//Mirror the Direction so that we can get the new trajectory of the ball
	Direction = Direction.MirrorByVector(HitNormal);

	//If the ball hits the paddle, add Z velocity to the ball (This can become very fast)
	if (Other->GetName().Equals("PlayerPaddle"))
	{
		APaddle* paddle = (APaddle*)Other;
		Direction.Z += (paddle->GetZVelocity() / Velocity);
	}
}

void ABall::Reset()
{
	Sprite->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	Sprite->SetRelativeScale3D(FVector(0.07f, 1.0f, 0.07f));
	Direction = FVector(0.0f, 0.0f, 0.0f);
	Velocity = 0.0f;
}

