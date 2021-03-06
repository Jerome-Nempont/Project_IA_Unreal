// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehiculeIA.h"
#include "VehiculePath.generated.h"

/**
 * 
 */
UCLASS()
class TP1_IA_API AVehiculePath : public AVehiculeIA
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AVehiculePath();

	class AGenerateLevels* Levels;

	UPROPERTY(EditAnywhere, Category = "Path")
	float DistanceChangePoint;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly)
	TSubclassOf<class ADestination> DestinationClass;

	FIntVector Start;
	FIntVector Depart;
	FIntVector Destination;
	FIntVector DestinationEnCours;
	TArray<FVector> ListPoint;
	TArray<TArray<FVector>> ListOtherPoint;

	int IndexList;

	bool IsCircuit;
	bool IsStart;
	bool IsArrival;
	bool NoDestination;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BindInput();
	void GenerateWay();
	void ChangeTargetOne();
	FVector CastToInt(FIntVector Vector);

public:
	virtual void Tick(float DeltaTime) override;

	void Click();
	void Swap();
	void StartCircuit();

	void SwapWay();

private:
	float f(FIntVector Point, float CostCourant);
	float Distance(FIntVector Point);
	bool CompareFIntVector(const FIntVector& A, const FIntVector& B);
	void AddWayInParcour();
	bool AddToList(int x, int y, float CostCourant, FIntVector Courant);
	void ReloadNewWay();
	void GenerateDestination(FIntVector Location);
};
