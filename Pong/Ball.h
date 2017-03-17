// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to start moving the Ball
	void StartMove();

	// notify hit
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// Reset the Ball
	void Reset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Reference to the Sprite Component which contains the ball sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ball)
	class UPaperSpriteComponent* Sprite;


private:

	
	//The direction the ball is traveling in
	FVector Direction;

	//Velocity of the ball.  How Fast it is travelling. Distance/Time
	float Velocity;
};
