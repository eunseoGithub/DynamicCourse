// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

class ATargetPoint;

UCLASS()
class DYNAMICCOURSE_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Components")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Points")
	TArray<ATargetPoint*> Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator")
	float AcceptanceRadius = 10.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	int32 CurrentIndex = 0;
	int32 Direction = 1;

	void AdvanceIndexPingPong();

};
