// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <functional>
#include <map>
#include "BlockBase.h"
#include "CoreMinimal.h"
typedef std::function<BlockBase* (int)> NewBlockFun;
/**
 * 
 */
class WORLD_API BlockMaterialManager
{
public:
	BlockMaterialManager();
	~BlockMaterialManager();
public:
	FORCEINLINE static BlockMaterialManager& Get()
	{
		if (!Singleton)
		{
			RegisterClasses();
			SetupSingleton();
			check(Singleton != nullptr);
		}
		return *Singleton;
	}
public:
	BlockBase* GetMaterial(int32 Id);
	void load();

	static BlockBase* CreateBlock(const std::string& className) {
		if (Creators().find(className) != Creators().end()) {
			return Creators()[className]();
		}
		else {
			return nullptr;
		}
	}


private:
	/** Singleton for the Block manager **/
	static  BlockMaterialManager* Singleton;

	/** Function to create the singleton **/
	static  void SetupSingleton();

	typedef  std::function<BlockBase* ()> CreatorFunction;
	static std::map<std::string, CreatorFunction>& Creators() {
		static std::map<std::string, CreatorFunction> creators;
		return creators;
	}
	static void RegisterClass(const std::string& className, CreatorFunction creator) {
		Creators()[className] = creator;
	}
	static void RegisterClasses();
private:
	std::map<int32, BlockBase*> BlockMaterials;
	//TArray<BlockBase*> BlockMaterials;
};
