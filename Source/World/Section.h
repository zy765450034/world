// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Block.h"
#include <map>
#include "Section.generated.h"

const int SectionSize = 16;

/**
 * 
 */
UCLASS()
class WORLD_API USection : public UObject
{
	GENERATED_BODY()
public:
	USection();
	int GetBlockIndex(int X, int Y, int Z) const;
	//UBlock GetNeighborBlock(EDirection Dir);
	void SetBlock(FVector Pos, int Id);
	FBlock GetBlock(FVector Pos);
	FBlock GetBlock(FString Number) const;
	bool isFullBlock() { return Numbers.Num() == SectionSize * SectionSize * SectionSize; };
public:
	FVector Origin;
	TMap<FString,int> Numbers;
	//TArray<FBlock> Blocks;
	std::map<int32, FBlock> Blocks;
	static long BlocksNumber;
	
};
