// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "Engine/TargetPoint.h"

// Sets default values
AElevator::AElevator()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	
	MoveSpeed = 100.0f;
	AcceptanceRadius = 10.0f;
	
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	Points.RemoveAll([](const ATargetPoint * p)
	{
		return p == nullptr;
	});

	if (Points.Num() > 0)
	{
		CurrentIndex = FMath::Clamp(CurrentIndex, 0, Points.Num() - 1);
		Direction = 1;
	}
	SetActorLocation(Points[0]->GetActorLocation());
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MoveSpeed <= 0.0f) 
		return;
	if (Points.Num() < 2) 
		return;

	ATargetPoint* Target = Points.IsValidIndex(CurrentIndex) ? Points[CurrentIndex] : nullptr;
	if (!Target) 
		return;

	const FVector Current = GetActorLocation();
	const FVector Goal = Target->GetActorLocation();

	const FVector Next = FMath::VInterpConstantTo(Current, Goal, DeltaTime, MoveSpeed);
	SetActorLocation(Next);

	const float Dist = FVector::Dist(Next, Goal);
	if (Dist <= AcceptanceRadius)
	{
		AdvanceIndexPingPong();
	}

	
}

void AElevator::AdvanceIndexPingPong()
{
	const int32 Last = Points.Num() - 1;

	if (CurrentIndex == Last)
		Direction = -1;
	else if (CurrentIndex == 0)
		Direction = 1;

	CurrentIndex += Direction;

	CurrentIndex = FMath::Clamp(CurrentIndex, 0, Last);
}