// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimePlatform.generated.h"

class UBoxComponent;
class UMaterialInterface;
class UStaticMeshComponent;
class USceneComponent;
UCLASS()
class DYNAMICCOURSE_API ATimePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimePlatform();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	void NotifyActorBeginOverlap(AActor* OtherActor);
	void NotifyActorEndOverlap(AActor* OtherActor);
	void ApplyOnStepMaterial();
	void ApplyPreDropMaterial();
	void DropPlatform();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimePlatform|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePlatform|Components")
	UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TimePlatform|Properties")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePlatform|Materials")
	UMaterialInterface* OnStepMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePlatform|Materials")
	UMaterialInterface* PreDropMaterial;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY()
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(VisibleAnywhere)
	bool bSteppedOn = false;

	UFUNCTION()
	void RestoreDefaultMaterial();

private:
	FTimerHandle PreDropTimerHandle;
	FTimerHandle DropTimerHandle;

};
