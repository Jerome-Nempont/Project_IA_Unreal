// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicule.h"

AVehicule::AVehicule()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVehicule::BeginPlay(){Super::BeginPlay();}
void AVehicule::Tick(float DeltaTime){Super::Tick(DeltaTime);}

FVector AVehicule::Truncate(FVector vec, float Max)
{
	if (vec.Size() > Max)
	{
		vec.Normalize();
		return  vec * Max;
	}
	else return vec;
}