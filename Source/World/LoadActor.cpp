// Fill out your copyright notice in the Description page of Project Settings.
#include "LoadActor.h"
#include "Engine/StaticMeshSourceData.h"
#include "RawMesh.h"

#include "Engine/StaticMesh.h"
#include "BlockManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include <Materials/MaterialExpressionTextureSample.h>
struct FTriangleIndices
{
    int32 v0;
    int32 v1;
    int32 v2;

    FTriangleIndices()
        : v0(INDEX_NONE), v1(INDEX_NONE), v2(INDEX_NONE)
    {}

    FTriangleIndices(int32 InV0, int32 InV1, int32 InV2)
        : v0(InV0), v1(InV1), v2(InV2)
    {}

    bool IsValid() const
    {
        return v0 != INDEX_NONE && v1 != INDEX_NONE && v2 != INDEX_NONE;
    }

    friend bool operator==(const FTriangleIndices& A, const FTriangleIndices& B)
    {
        return A.v0 == B.v0 && A.v1 == B.v1 && A.v2 == B.v2;
    }

    friend bool operator!=(const FTriangleIndices& A, const FTriangleIndices& B)
    {
        return !(A == B);
    }
};
DEFINE_LOG_CATEGORY_STATIC(LogLearnRawMesh, Log, All);
// Sets default values
ALoadActor::ALoadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ���� StaticMeshComponent
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));

	// ���� RootComponent Ϊ StaticMeshComponent
	RootComponent = StaticMeshComponent;

 

    // ���� StaticMesh
    //UStaticMesh* NewMesh = CreateStaticMeshFromRawMesh(RawMesh);
	UStaticMesh* NewMesh = CreateRawMesh();
    // �� StaticMesh ����� StaticMeshComponent
    StaticMeshComponent->SetStaticMesh(NewMesh);
	
}


UStaticMesh* ALoadActor::CreateRawMesh()
{
	TArray<FVector3f> Vertices = {
		FVector3f(0, 0, 0),  // ���� 0
		FVector3f(100, 0, 0),  // ���� 1
		FVector3f(100, 100, 0),  // ���� 2
		FVector3f(0, 100, 0),  // ���� 3
		FVector3f(0, 0, 100),  // ���� 4
		FVector3f(100, 0, 100),  // ���� 5
		FVector3f(100, 100, 100),  // ���� 6
		FVector3f(0, 100, 100)  // ���� 7
	};

	// ���巽�����������
	
	TArray<uint32> Triangles = {
		 0, 1, 2, 0, 2, 3,   // Front face
		1, 5, 6, 1, 6, 2,   // Right face
		4, 7, 6, 4, 6, 5,   // Back face
		0, 3, 7, 0, 7, 4,   // Left face
		3, 2, 6, 3, 6, 7,   // Top face
		0, 4, 5, 0, 5, 1    // Bottom face
	};
	FRawMesh RawMesh;
	RawMesh.VertexPositions = Vertices;
	RawMesh.WedgeIndices = Triangles;


	for (size_t i = 0; i < 6; i++)
	{
		RawMesh.WedgeTexCoords[0].Add(FVector2f(1, 1));
		RawMesh.WedgeTexCoords[0].Add(FVector2f(1, 0));
		RawMesh.WedgeTexCoords[0].Add(FVector2f(0, 0));
		
		RawMesh.WedgeTexCoords[0].Add(FVector2f(0, 0));
		RawMesh.WedgeTexCoords[0].Add(FVector2f(1, 1));
		RawMesh.WedgeTexCoords[0].Add(FVector2f(1, 0));
		
	}

	for (size_t i = 0; i < 12; i++)
	{
		RawMesh.FaceMaterialIndices.Add(i);
		
		RawMesh.FaceSmoothingMasks.Add(i);
	}


	for (int32 i = 0; i < 6; ++i) // �������� 4 ������
	{
		RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
		RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
		RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
		RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
		RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
		RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));

		RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
		RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
		RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
		RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
		RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
		RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));

		RawMesh.WedgeTangentZ.Add(FVector3f(0, 0, 1));
		RawMesh.WedgeTangentZ.Add(FVector3f(0, 0, 1));
		RawMesh.WedgeTangentZ.Add(FVector3f(0, 0, 1));
		RawMesh.WedgeTangentZ.Add(FVector3f(0, 0, 1));
		RawMesh.WedgeTangentZ.Add(FVector3f(0, 1, 0));
		RawMesh.WedgeTangentZ.Add(FVector3f(0, 1, 0));
	}

	if (RawMesh.IsValid())
	{
		UStaticMesh* NewMesh = NewObject<UStaticMesh>();

		NewMesh->InitResources();

		const TArray<FStaticMeshSourceModel>& SourceModels = NewMesh->GetSourceModels();

		const FStaticMeshSourceModel& SrcModel = NewMesh->AddSourceModel();
		FRawMeshBulkData* BulkData = SrcModel.RawMeshBulkData;
		BulkData->SaveRawMesh(RawMesh);

		UMaterial* Material = NewObject<UMaterial>();
		int BlockSize = 100;
		//UTexture2D* Texture = NewObject<UTexture2D>(InParent, *FString::Printf(TEXT("%s_TX"), BlockBase::GetName(Id).GetPlainNameString()), RF_Public);
		UTexture2D* Texture = UTexture2D::CreateTransient(BlockSize, BlockSize, PF_B8G8R8A8);
		uint8* Pixels = static_cast<uint8*>(Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FColor FillColor = FColor(0xffff66ff);
		// ��������ÿ������
		for (int32 Y = 0; Y < BlockSize; Y++)
		{
			for (int32 X = 0; X < BlockSize; X++)
			{
				int32 Index = (Y * BlockSize + X) * 4; // BGRA ��ʽ��ÿ������ 4 ���ֽ�
				Pixels[Index + 0] = FillColor.B;   // Blue
				Pixels[Index + 1] = FillColor.G;   // Green
				Pixels[Index + 2] = FillColor.R;   // Red
				Pixels[Index + 3] = FillColor.A;   // Alpha
			}
		}

		// ��������
		Texture->PlatformData->Mips[0].BulkData.Unlock();

		// ����������Դ
		Texture->UpdateResource();
		if (Texture)
		{
			Material->TwoSided = false;
			Material->SetShadingModel(MSM_DefaultLit);
			UMaterialExpressionTextureSample* Expression = NewObject<UMaterialExpressionTextureSample>(Material);
			auto EditorOnly = Material->GetEditorOnlyData();
			EditorOnly->ExpressionCollection.AddExpression(Expression);
			EditorOnly->BaseColor.Expression = Expression;
			Expression->Texture = Texture;
			Material->PostEditChange();
		}
		//NewMesh->SetMaterial(0,Material);
		//NewMesh->SetMaterial(4, Material);
		
		NewMesh->GetStaticMaterials().Add(FStaticMaterial(Material));
		NewMesh->GetStaticMaterials().Add(FStaticMaterial(Material));
		NewMesh->GetStaticMaterials().Add(FStaticMaterial(Material));
		NewMesh->GetStaticMaterials().Add(FStaticMaterial(Material));
		NewMesh->Build(false);
		FAssetRegistryModule::AssetCreated(NewMesh);
		return NewMesh;
	}
	return nullptr;
	return nullptr;;
}





void ALoadActor::LogRawMesh()
{
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	
	
}

// Called when the game starts or when spawned
void ALoadActor::BeginPlay()
{
	Super::BeginPlay();
	//LogRawMesh();
	//BlockManager::Get().load();
	//BlockManager::Get().CreateStaticMesh(this, FName(TEXT("MyName")), RF_Public);
	
}

// Called every frame
void ALoadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

