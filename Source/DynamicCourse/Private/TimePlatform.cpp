// Fill out your copyright notice in the Description page of Project Settings.


#include "TimePlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
ATimePlatform::ATimePlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 90.0f;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(SceneRoot);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATimePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	if (StaticMeshComp)
	{
		DefaultMaterial = StaticMeshComp->GetMaterial(0);
	}

}

// Called every frame
void ATimePlatform::Tick(float DeltaTime)
{

}

void ATimePlatform::ApplyOnStepMaterial()
{
	if (StaticMeshComp && OnStepMaterial)
	{
		StaticMeshComp->SetMaterial(0, OnStepMaterial);
	}
}
void ATimePlatform::ApplyPreDropMaterial()
{
	if (StaticMeshComp && PreDropMaterial)
	{
		StaticMeshComp->SetMaterial(0, PreDropMaterial);
	}
}

void ATimePlatform::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor || OtherActor == this || !OtherActor->IsA<APawn>())
	{
		return;
	}

	if (bSteppedOn)
		return;

	bSteppedOn = true;

	ApplyOnStepMaterial();

	GetWorldTimerManager().SetTimer(PreDropTimerHandle, this,&ATimePlatform::ApplyPreDropMaterial, 2.0f, false);

	GetWorldTimerManager().SetTimer(DropTimerHandle, this, &ATimePlatform::DropPlatform, 3.0f, false);

}
void ATimePlatform::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor || OtherActor == this || !OtherActor->IsA<APawn>())
	{
		return;
	}

	bSteppedOn = false;

	GetWorldTimerManager().ClearTimer(PreDropTimerHandle);
	GetWorldTimerManager().ClearTimer(DropTimerHandle);

	RestoreDefaultMaterial();
}

void ATimePlatform::RestoreDefaultMaterial()
{
	if (StaticMeshComp && DefaultMaterial)
	{
		StaticMeshComp->SetMaterial(0, DefaultMaterial);
	}
}
void ATimePlatform::DropPlatform()
{
	if (!StaticMeshComp)
	{
		return;
	}

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StaticMeshComp->SetSimulatePhysics(true);
}
