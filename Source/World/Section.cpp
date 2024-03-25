// Fill out your copyright notice in the Description page of Project Settings.


#include "Section.h"


long USection::BlocksNumber = 0;

USection::USection() {
	//Blocks.SetNum(SectionSize * SectionSize * SectionSize, false); 
	
};

int USection::GetBlockIndex(int X, int Y, int Z) const
{
	return Z * SectionSize * SectionSize + Y * SectionSize + X;
}

//UBlock* USection::GetNeighborBlock(EDirection Dir)
//{
//}

void USection::SetBlock(FVector Pos, int Id)
{
	FBlock Block =  GetBlock(Pos);
	if (!Block.IsActive)
	{
		Block.Id = Id;
		Block.Pos = Pos;
		Block.IsActive = true;
		Blocks[GetBlockIndex(Pos.X, Pos.Y, Pos.Z)] = Block;
		Numbers.Add(FString::Printf(TEXT("%ld"), BlocksNumber, GetBlockIndex(Pos.X, Pos.Y, Pos.Z)));
		BlocksNumber++;
	}
	else
	{
		Block.Id = Id;
		Blocks[GetBlockIndex(Pos.X, Pos.Y, Pos.Z)] = Block;
	}
		
		

}

FBlock USection::GetBlock(FVector Pos)
{
	//if (Origin.X >= Pos.X && Origin.Y >= Pos.Y && Origin.Z >= Pos.X)
	//{
		return Blocks[GetBlockIndex(Pos.X, Pos.Y, Pos.Z)];
	//}
	//return FBlock();
}
FBlock USection::GetBlock(FString Number) const
{
	const int32* index = Numbers.Find(Number);
	if (index != nullptr)
	{
		//return Blocks[*index];
	}
	FBlock Block;
	return Block;
}