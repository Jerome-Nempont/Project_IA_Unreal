// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiculeCircuit.h"

AVehiculeCircuit::AVehiculeCircuit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVehiculeCircuit::BeginPlay()
{
	Super::BeginPlay();
}

void AVehiculeCircuit::Tick(float DeltaTime)
{
	if (AlgoCircuit == AlgoCuircuit::CIRCUIT) ChangeTargetCircuit();
	else if (AlgoCircuit == AlgoCuircuit::TWO_WAY) ChangeTargetTwo(DeltaTime);
	else ChangeTargetOne();

	FVector SteeringDirection = CalculDirection();

	FVector SteeringForce = Truncate(SteeringDirection, MaxForce);
	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate(Velocity + Acceleration, MaxSpeed);
	SetActorLocation(GetActorLocation() + Velocity);

	SetActorRotation(FRotator(Velocity.Rotation()));
}

void AVehiculeCircuit::ChangeTargetCircuit()
{
	FVector target = ListTargets[IndexList]->GetActorLocation();
	float dist = (target - GetActorLocation()).Size();
	if (dist <= DistanceChangeTarget) IndexList += Direction;
	if (IndexList >= ListTargets.Num()) IndexList = 0;
}

void AVehiculeCircuit::ChangeTargetTwo(float DeltaTime)
{
	FVector target = ListTargets[IndexList]->GetActorLocation();
	float dist = (target - GetActorLocation()).Size();

	if (IsArrival)
	{
		if (dist <= 1.f) IsTarget = true;

		if (IsTarget)
		{
			TimeWaitCurrent -= DeltaTime;

			if (TimeWaitCurrent <= 0)
			{
				Direction = -Direction;
				IsArrival = false;
				IsTarget = false;
			}
		}
		
		return;
	}

	if (dist <= DistanceChangeTarget) IndexList += Direction;
	if (IndexList >= ListTargets.Num())
	{
		IsArrival = true;
		IndexList = ListTargets.Num() - 1;
		TimeWaitCurrent = TimeWait;
	}
	else if (IndexList <= 0 && Direction == -1)
	{
		IsArrival = true;
		IndexList = 0;
		TimeWaitCurrent = TimeWait;
	}
}

void AVehiculeCircuit::ChangeTargetOne()
{
	if (IsArrival) return;

	FVector target = ListTargets[IndexList]->GetActorLocation();
	float dist = (target - GetActorLocation()).Size();
	
	if (dist <= DistanceChangeTarget) IndexList += Direction;
	if (IndexList >= ListTargets.Num())
	{
		IsArrival = true;
		IndexList = ListTargets.Num() - 1;
	}
}

FVector AVehiculeCircuit::CalculDirection()
{
	FVector target = ListTargets[IndexList]->GetActorLocation();

	if (IsArrival) return ArrivalVelocity(target);
	return SeekVelocity(target);
}