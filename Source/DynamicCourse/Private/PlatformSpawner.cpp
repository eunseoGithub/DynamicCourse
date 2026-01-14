// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "TimePlatform.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#define XOFFSET 20
#define YOFFSET 20

// Sets default values
APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SetRootComponent(SpawnArea);

	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!platformClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[PlatformSpawner] PlatformClass is not set on %s"), *GetName());
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[PlatformSpawner] World is null on %s"), *GetName());
		return;
	}

	SpawnedPlatform.Reset();
	SpawnedPlatform.Reserve(SpawnCount);

	for (int32 i = 0; i < SpawnCount; ++i)
	{
		FVector SpawnLoc;
		const bool bFound = FindSpawnLocation(SpawnLoc);

		if (!bFound)
		{
			UE_LOG(LogTemp, Warning, TEXT("[PlatformSpawner] Failed to find location"));
			continue;
		}

		const FRotator SpawnRot(0.f, FMath::FRandRange(0.f, 360.f), 0.f);
		
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ATimePlatform* Spawned = World->SpawnActor<ATimePlatform>(platformClass, SpawnLoc, SpawnRot, Params);
		if (Spawned)
		{
			SpawnedPlatform.Add(Spawned);
		}
	}
}
FVector APlatformSpawner::GetRandomPointXY() const
{
	const FVector Origin = SpawnArea->GetComponentLocation();
	const FVector Extent = SpawnArea->GetScaledBoxExtent();

	const float X = FMath::FRandRange(-(Extent.X + XYExpand), (Extent.X + XYExpand));
	const float Y = FMath::FRandRange(-(Extent.Y + XYExpand), (Extent.Y + XYExpand));

	return FVector(Origin.X + X, Origin.Y + Y, FixedSpawnZ);
}

bool APlatformSpawner::ISFarEnoughFromAll(const FVector& Candidate) const
{
	for (const ATimePlatform* p : SpawnedPlatform)
	{
		if (!p) continue;

		const float Dist2D = FVector::Dist2D(p->GetActorLocation(), Candidate);
		if (Dist2D < MinSpacing)
		{
			return false;
		}
	}
	return true;
}

bool APlatformSpawner::IsValidCandidate(const FVector& Candidate, const FVector& Base) const
{
	if (!ISFarEnoughFromAll(Candidate))
	{
		return false;
	}

	if (bUseJumpBand && SpawnedPlatform.Num() > 0)
	{
		const float DistFromBase = FVector::Dist2D(Base, Candidate);

		if (DistFromBase < MinSpacing || DistFromBase > MaxSpacing)
		{
			return false;
		}
	}
	return true;
}

bool APlatformSpawner::FindSpawnLocation(FVector& OutLocation) const
{
	const FVector Base = (SpawnedPlatform.Num() > 0) ? SpawnedPlatform.Last()->GetActorLocation() : SpawnArea->GetComponentLocation();

	for (int32 i = 0; i < MaxTriesPerPlatform; ++i)
	{
		const FVector Candidate = GetRandomPointXY();

		if (SpawnedPlatform.Num() == 0)
		{
			OutLocation = Candidate;
			return true;
		}
		if (IsValidCandidate(Candidate, Base))
		{
			OutLocation = Candidate;
			return true;
		}
	}
	return false;
}
