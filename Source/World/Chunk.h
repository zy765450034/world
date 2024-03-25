// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Chunk.generated.h"
struct FBlock;
class USection;
const int ChunkSize = 16;
//const int ChunkHigh = ChunkSize*ChunkSize;
/**
 * 
 */
UCLASS()
class WORLD_API UChunk : public UObject
{
	GENERATED_BODY()
	
public:
	UChunk();
	void SetBlock(FVector Pos, int Id);
	FBlock GetBlock(FVector Pos);
	USection* GetSectionByY(int Y);
	void CreateStaticMesh(UObject* InParent, FName InName, EObjectFlags Flags) const;
	int GetIndex();
	int GetIndexMax();
	FVector Origin;
public:
	UPROPERTY(EditDefaultsOnly, EditFixedSize, Category = Voxel)
	TArray<UStaticMesh*> Mesh;
private:
	TArray<USection*> Sections;
};
