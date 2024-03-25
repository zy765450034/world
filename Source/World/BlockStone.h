// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BlockBase.h"
#include "CoreMinimal.h"

/**
 * 
 */
class WORLD_API BlockStone: public BlockBase
{
public:
	BlockStone();
	~BlockStone();
public:
	bool Check(FVector Position) const;
public:
	virtual void initMaterial(int32 Id) override;
	virtual void CreateMesh(UObject* InParent, FName InName, EObjectFlags Flags, FVector Position) override;
	virtual bool CreateTexture(UTexture2D* const& OutTexture) const override;
public:
	int BlockId;
	UMaterial* Material;
	UStaticMesh* StaticMesh;
};
