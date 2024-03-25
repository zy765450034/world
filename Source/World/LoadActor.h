// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadActor.generated.h"

UCLASS()
class WORLD_API ALoadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoadActor();
	UPROPERTY(Category = "RawMeshLogger", EditAnywhere)
		UStaticMesh* StaticMesh;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION(Category = "RawMeshLogger", CallInEditor)
		void LogRawMesh();
	
	UStaticMesh* CreateRawMesh();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
