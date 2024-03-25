// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Block.h"
#include <Materials/MaterialExpressionTextureSample.h>
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum  EBlock : int32
{
	Null=0, Air, Stone, Dirt, Grass, BlockId_Max
};





struct FBlockMeshData
{
 
public:
    TArray<FVector3f> Vertices;
    TArray<uint32> Triangles;
    TArray<FVector> Normals;
    TArray<FColor> Colors;
    TArray<FVector2f> UV0;

    void Clear();
};

inline void FBlockMeshData::Clear()
{
    Vertices.Empty();
    Triangles.Empty();
   // Normals.Empty();
   // Colors.Empty();
   // UV0.Empty();
}

class WORLD_API BlockBase
{
public:
	
	BlockBase();
	~BlockBase();
public:
	virtual void initMaterial(int32 Id) = 0;
	virtual void CreateMesh(UObject* InParent, FName InName, EObjectFlags Flags, FVector Position) = 0;
	virtual bool CreateTexture(UTexture2D* const& OutTexture) const = 0;
	static FName GetName(int32 Id);
    void CreateFace(EBDirection Direction, FVector Position);
    FVector GetNormal(const EBDirection Direction) const;
    TArray<FVector3f> GetFaceVertices(EBDirection Direction, FVector Position) const;
    TArray<uint32> GetFaceTriangles(EBDirection Direction) const;
    FVector GetPositionInDirection(EBDirection Direction, FVector Position) const;
public:
    const FVector BlockVertexData[8] = {
        FVector(BlockSize,BlockSize,BlockSize),
        FVector(BlockSize,0,BlockSize),
        FVector(BlockSize,0,0),
        FVector(BlockSize,BlockSize,0),
        FVector(0,0,BlockSize),
        FVector(0,BlockSize,BlockSize),
        FVector(0,BlockSize,0),
        FVector(0,0,0)
    };

    const int BlockTriangleData[24] = {
        0,1,2,3, // Forward
        5,0,3,6, // Right
        4,5,6,7, // Back
        1,4,7,2, // Left
        5,4,1,0, // Up
        3,2,7,6  // Down
    };
    uint32 VertexCount = 0;
    FBlockMeshData MeshData;
	UMaterial* Material = nullptr;
};
