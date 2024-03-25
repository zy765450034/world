// Fill out your copyright notice in the Description page of Project Settings.
#include "BlockManager.h"
#include "Block.h"
#include "Section.h"
#include "Chunk.h"
#include "SectionTask.h"
#include "VoxelModel/mv_xraw.h"
#include "VoxelModel/mv_vox.h"
#include "VoxelModel/mv_lib.h"
#include <RawMesh.h>
#include "BlockMaterialManager.h"

//const int hith = SectionSize;
//const int width = SectionSize * SectionSize * SectionSize;
//const int length = SectionSize * SectionSize * SectionSize;
const int ChunkNumber = 17;

int GetBlockSection(int x) 
{
    int n = x / SectionSize;
    return (x - n * SectionSize < 0) ? n - 1 : n;
}

FVector GetSection(FVector& Pos) 
{
    return FVector(GetBlockSection(Pos.X), GetBlockSection(Pos.Y), GetBlockSection(Pos.Z));
}

BlockManager* BlockManager::Singleton = nullptr;

void BlockManager::SetupSingleton()
{
	check(!Singleton);
	LLM_SCOPE_BYNAME(TEXT("BlockManager"));
	if (!Singleton)
	{
		Singleton = new BlockManager; // we will leak this
	}
	check(Singleton);
}

BlockManager::BlockManager()
{
    //Chunks.SetNum(ChunkNumber* ChunkNumber);
}
void BlockManager::load()
{

    MV_Model vox;
    vox.LoadModel("H:/World/Content/VoxelData/cars.vox");
    for (size_t i = 0; i < 1; i++)
    {
        MV_Voxel v = vox.voxels[i];
        FVector Vec= FVector(v.x, v.y, v.z);
        SetBlock(Vec, v.colorIndex);
        FBlock Block = GetBlock(Vec);
        BlockBase* BlockMtl = BlockMaterialManager::Get().GetMaterial(Block.Id);
       
        BlockMtl->CreateMesh(nullptr, FName(TEXT("MyName")), RF_Public, Vec);
    }

    FGraphEventRef MyTaskGraph = FFunctionGraphTask::CreateAndDispatchWhenReady(
        [&]()
        {
            // 在任务图中执行任务
            SectionTask::DoWork();
        },
        TStatId(),
            nullptr,
            ENamedThreads::AnyThread
            );
}

bool BlockManager::SetBlock(FVector& Pos, int Id)
{
    FVector Vec = GetSection(Pos);
    UChunk* Chunk = GetChunk(Vec);
    if (Chunk)
    {
        FVector CPos = Pos - Chunk->Origin;
        Chunk->SetBlock(CPos, Id); 
    }
    return false;
}

FBlock BlockManager::GetBlock(FVector Pos)
{
    FBlock Block;
    FVector Vec = GetSection(Pos);
    UChunk* Chunk = GetChunk(Vec);
    if (Chunk)
    {
        FVector CPos = Pos - Chunk->Origin;
        Block = Chunk->GetBlock(CPos);
    }
    return Block;
}

UChunk* BlockManager::GetChunk(FVector& Pos)
{
    UChunk* Chunk = Chunks[Pos.X * ChunkNumber + Pos.Y];
    if (!Chunk)
    {
        Chunk = NewObject<UChunk>();
        Chunk->Origin = FVector(Pos.X * SectionSize, Pos.Y * SectionSize,0);
        Chunks[Pos.X * ChunkNumber + Pos.Y] = Chunk;
    }
    return Chunk;
}

void BlockManager::CreateStaticMesh(UObject* InParent, FName InName, EObjectFlags Flags) const
{
    for (const auto& pair : Chunks) {
        UChunk* Chunk = pair.second;
        for (size_t ix = 0; ix < ChunkSize; ix++)
        {
            USection* Section = Chunk->GetSectionByY(ix);
            for (size_t X = 0; X < SectionSize; X++)
            {
                for (size_t Y = 0; Y < SectionSize; Y++)
                {
                    for (size_t Z = 0; Z < SectionSize; Z++)
                    {
                        FVector Pos = FVector(X, Y, Z) + Chunk->Origin;
                        FBlock Block = Section->GetBlock(Pos);
                        if (Block.Id != 0)
                        {
                            BlockBase* BlockMtl = BlockMaterialManager::Get().GetMaterial(Block.Id);
                            BlockMtl->CreateMesh(InParent, InName, Flags, Pos);
                        }
                      

                    }
                }
            }
        }
    }
}

BlockManager::~BlockManager()
{
}


