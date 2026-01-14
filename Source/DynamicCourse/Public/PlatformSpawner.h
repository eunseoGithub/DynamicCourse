// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"
class ATimePlatform;
class UBoxComponent;
UCLASS()
class DYNAMICCOURSE_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:	
	APlatformSpawner();
private:
	FVector GetRandomPointXY() const;
	bool ISFarEnoughFromAll(const FVector& Candidate) const;
	bool FindSpawnLocation(FVector& OutLocation) const;
	bool IsValidCandidate(const FVector& Candidate, const FVector& Base) const;
private:
	UPROPERTY(VisibleAnywhere, Category = "Spawn|Components")
	UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, Category = "Spawn|Config")
	TSubclassOf<ATimePlatform> platformClass;

	UPROPERTY(EditAnywhere, Category = "Spawn|Config", meta = (ClampMin = "1"))
	int32 SpawnCount = 10;

	UPROPERTY(EditAnywhere, Category = "Spawn|Placement")
	float FixedSpawnZ = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn|Placement", meta = (ClampMin = "0.0"))
	float MinSpacing = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn|Placement", meta = (ClampMin = "0.0"))
	float MaxSpacing = 650.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn|Placement")
	bool bUseJumpBand = true;

	UPROPERTY(EditAnywhere, Category = "Spawn|Placement", meta = (ClampMin = "1"))
	int32 MaxTriesPerPlatform = 40;

	UPROPERTY(EditAnywhere, Category = "Spawn|Placement")
	float XYExpand = 20.0f;

	UPROPERTY()
	TArray<ATimePlatform*> SpawnedPlatform;
};
