// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
struct FBlock;
class UChunk;
/**
 * 
 */
class WORLD_API BlockManager
{
public:
	BlockManager();
	~BlockManager();
public:
	FORCEINLINE static BlockManager& Get()
	{
		if (!Singleton)
		{
			SetupSingleton();
			check(Singleton != nullptr);
		}
		return *Singleton;
	}
	void load();
public:
	bool SetBlock(FVector& Pos,int Id);
	FBlock GetBlock(FVector Pos);
	UChunk* GetChunk(FVector& Pos);
	void CreateStaticMesh(UObject* InParent, FName InName, EObjectFlags Flags) const;
private:
	/** Singleton for the Block manager **/
	static  BlockManager* Singleton;

	/** Function to create the singleton **/
	static  void SetupSingleton();
	std::map<int32, UChunk*> Chunks;
	//TMap<FVector,UChunk*> Chunks;
};
