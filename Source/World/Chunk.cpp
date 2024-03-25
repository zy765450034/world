// Fill out your copyright notice in the Description page of Project Settings.
#include "Chunk.h"
#include "Section.h"



UChunk::UChunk() { 
	for (size_t i = 0; i < ChunkSize; i++)
	{
		USection* NewSection = NewObject<USection>();
		Sections.Add(NewSection);
	}
};

void UChunk::SetBlock(FVector Pos, int Id)
{
	USection* Section = GetSectionByY(Pos.Y);
	Section->SetBlock(Pos, Id);
}
FBlock UChunk::GetBlock(FVector Pos)
{
	USection* Section = GetSectionByY(Pos.Y);
	
	return Section->GetBlock(Pos);
}
USection* UChunk::GetSectionByY(int Y)
{
	return Sections[Y];
}

void UChunk::CreateStaticMesh(UObject* InParent, FName InName, EObjectFlags Flags) const
{
	
}

int UChunk::GetIndex()
{
	return ChunkSize;
}
int UChunk::GetIndexMax()
{
	return ChunkSize;
}