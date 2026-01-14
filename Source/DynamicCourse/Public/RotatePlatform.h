// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatePlatform.generated.h"

UCLASS()
class DYNAMICCOURSE_API ARotatePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatePlatform();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RotatePlatform|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatePlatform|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RotatePlatform|Properties")
	float RotationSpeed;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:	
	

};
