// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vehicule.generated.h"

UCLASS()
class TP1_IA_API AVehicule : public AActor
{
	GENERATED_BODY()
	
public:	

	AVehicule();
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE FVector GetVelocity() { return Velocity; };
	FVector Truncate(FVector vec, float Max);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Physic")
	float Mass = 10.f;
	UPROPERTY(EditAnywhere, Category = "Physic")
	float MaxForce = 1.f;
	UPROPERTY(EditAnywhere, Category = "Physic")
	float MaxSpeed = 10.f;
	UPROPERTY(EditAnywhere, Category = "Physic")
	FVector Velocity;
};
