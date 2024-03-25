// Fill out your copyright notice in the Description page of Project Settings.
#include "BlockMaterialManager.h"
#include "Block.h"
#include "BlockBase.h"
#include "BlockStone.h"



BlockMaterialManager::BlockMaterialManager()
{
	//BlockMaterials.SetNum((int32)EBlock::BlockId_Max);
}

BlockMaterialManager::~BlockMaterialManager()
{
}

BlockMaterialManager* BlockMaterialManager::Singleton = nullptr;

void BlockMaterialManager::SetupSingleton()
{
	check(!Singleton);
	LLM_SCOPE_BYNAME(TEXT("BlockManager"));
	if (!Singleton)
	{
		Singleton = new BlockMaterialManager; // we will leak this
	}
	check(Singleton);
}

BlockBase* BlockMaterialManager::GetMaterial(int32 Id)
{
	if (!BlockMaterials[Id])
	{
		BlockMaterials[Id] = CreateBlock(TCHAR_TO_UTF8(*BlockBase::GetName(Id).ToString()));
		BlockMaterials[Id]->initMaterial(Id);
	}
	return BlockMaterials[Id];
}
void BlockMaterialManager::load()
{

}

void BlockMaterialManager::RegisterClasses() {
	RegisterClass("Stone", []() { return new BlockStone(); });
}