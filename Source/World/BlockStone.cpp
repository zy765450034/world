// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockStone.h"
#include "RawMesh.h"
#include "Engine/StaticMeshSourceData.h"
#include "Engine/StaticMesh.h"
#include "BlockManager.h"


BlockStone::BlockStone()
{
}

BlockStone::~BlockStone()
{
}

void BlockStone::initMaterial(int32 Id)
{
	BlockId = Id;
	Material = NewObject<UMaterial>();
	
	//UTexture2D* Texture = NewObject<UTexture2D>(InParent, *FString::Printf(TEXT("%s_TX"), BlockBase::GetName(Id).GetPlainNameString()), RF_Public);
	UTexture2D* Texture = UTexture2D::CreateTransient(BlockSize, BlockSize, PF_B8G8R8A8);
	if (CreateTexture(Texture))
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
}

bool BlockStone::Check(FVector Position) const
{
	FBlock block = BlockManager::Get().GetBlock(Position);
	if (block.Id == EBlock::Stone)
	{
		return true;
	}
	return false;
}


void BlockStone::CreateMesh(UObject* InParent, FName InName, EObjectFlags Flags,FVector Position)
{
	/*for (auto Direction : { EDirection::Forward, EDirection::Right, EDirection::Back, EDirection::Left, EDirection::Up, EDirection::Down })
	{
		//if (Check(GetPositionInDirection(Direction, Position)))
		{
			CreateFace(Direction, Position * BlockSize);
		}
	}
	FColor FillColor = FColor(0xffff66ff);
	FRawMesh OutRawMesh;
	OutRawMesh.VertexPositions = MeshData.Vertices;
	OutRawMesh.WedgeIndices = MeshData.Triangles;
	OutRawMesh.WedgeColors = MeshData.Colors;
	for (size_t i = 0; i < MeshData.UV0.Num(); i++)
	{
		OutRawMesh.WedgeTexCoords[0].Add(MeshData.UV0[i]);
	}

	//测试RawMesh
	FRawMesh RawMesh;
	//顶点位置数据，一个直角三角形
	RawMesh.VertexPositions.Add(FVector3f(0, 0, 0));
	RawMesh.VertexPositions.Add(FVector3f(1, 0, 0));
	RawMesh.VertexPositions.Add(FVector3f(1, 1, 0));
	//索引数据
	RawMesh.WedgeIndices.Add(0);
	RawMesh.WedgeIndices.Add(1);
	RawMesh.WedgeIndices.Add(2);
	//接下来的数据并不重要，只是需要满足Array的长度以能通过 FRawMesh::IsValid()
	RawMesh.WedgeTexCoords->Add(FVector2f(0, 0));
	RawMesh.WedgeTexCoords->Add(FVector2f(1, 0));
	RawMesh.WedgeTexCoords->Add(FVector2f(1, 1));
	RawMesh.FaceMaterialIndices.Add(0);
	RawMesh.FaceSmoothingMasks.Add(0);
	RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
	RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
	RawMesh.WedgeTangentX.Add(FVector3f(1, 0, 0));
	RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
	RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
	RawMesh.WedgeTangentY.Add(FVector3f(0, 1, 0));
	RawMesh.WedgeTangentZ.Add(FVector3f(0, 0, 1));
	RawMesh.WedgeTangentZ.Add(FVector3f(0, 0, 1));
	RawMesh.WedgeTangentZ.Add(FVector3f(0, 0, 1));
	

	if (RawMesh.IsValid())
	{
		//设定模型名字
		FString MeshName = "TestSM";
		//设定包的路径
		//FString PackageName = "/Game/" + MeshName;
		const TCHAR* PackageName = TEXT("/Game/TestSM");
		//创建包
		UPackage* MeshPackage = CreatePackage(PackageName);
		//创建StaticMesh资源
		StaticMesh = NewObject< UStaticMesh >(MeshPackage, FName(*MeshName), RF_Public | RF_Standalone);
		StaticMesh->PreEditChange(nullptr);
		// StaticMesh = NewObject<UStaticMesh>();
		//FMeshBuildSettings BuildSettings;
		FStaticMeshSourceModel& StaticMeshSourceModel = StaticMesh->AddSourceModel();
		//StaticMeshSourceModel.BuildSettings = BuildSettings;
		StaticMeshSourceModel.RawMeshBulkData->SaveRawMesh(RawMesh);

		StaticMesh->Build(true);
	}
	
	

	/*for (size_t i = 0; i < MeshData.Vertices.Num(); i++)
	{
		OutRawMesh.VertexPositions.Add(MeshData.Vertices[i]);
	}
	for (size_t i = 0; i < MeshData.Triangles.Num(); i++)
	{
		OutRawMesh.WedgeIndices.Add(MeshData.Triangles[i]);
	}*/

	// 创建一个 UStaticMesh 对象
	StaticMesh = NewObject<UStaticMesh>();

	// 定义方块的顶点坐标
	TArray<FVector3f> Vertices = {
		FVector3f(0, 0, 0),  // 顶点 0
		FVector3f(100, 0, 0),  // 顶点 1
		FVector3f(100, 100, 0),  // 顶点 2
		FVector3f(0, 100, 0),  // 顶点 3
		FVector3f(0, 0, 100),  // 顶点 4
		FVector3f(100, 0, 100),  // 顶点 5
		FVector3f(100, 100, 100),  // 顶点 6
		FVector3f(0, 100, 100)  // 顶点 7
	};

	// 定义方块的三角形面
	TArray<uint32> Triangles = {
		 0, 1, 2, 0, 2, 3,   // Front face
		1, 5, 6, 1, 6, 2,   // Right face
		4, 7, 6, 4, 6, 5,   // Back face
		0, 3, 7, 0, 7, 4,   // Left face
		3, 2, 6, 3, 6, 7,   // Top face
		0, 4, 5, 0, 5, 1    // Bottom face
	};

	// 创建一个 FRawMesh 对象，并设置顶点和三角形面
	FRawMesh RawMesh;
	RawMesh.VertexPositions = Vertices;
	RawMesh.WedgeIndices = Triangles;
	if (RawMesh.IsValid())
	{
		// 声明一个 FStaticMeshSourceModel 对象，并设置其顶点数据
		FStaticMeshSourceModel& SourceModel = StaticMesh->AddSourceModel();
		SourceModel.RawMeshBulkData->SaveRawMesh(RawMesh);

		// 构建 StaticMesh
		StaticMesh->Build(false);
	}
	

	
}

bool BlockStone::CreateTexture(UTexture2D* const& OutTexture) const
{
	
	check(OutTexture);
	
	// 创建一个新的 UTexture2D 对象
	//UTexture2D* NewTexture = UTexture2D::CreateTransient(BlockSize, BlockSize, PF_B8G8R8A8);
	// 锁定纹理以便写入像素数据
	uint8* Pixels = static_cast<uint8*>(OutTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	FColor FillColor = FColor(0xffff66ff);
	// 填充纹理的每个像素
	for (int32 Y = 0; Y < BlockSize; Y++)
	{
		for (int32 X = 0; X < BlockSize; X++)
		{
			int32 Index = (Y * BlockSize + X) * 4; // BGRA 格式，每个像素 4 个字节
			Pixels[Index + 0] = FillColor.B;   // Blue
			Pixels[Index + 1] = FillColor.G;   // Green
			Pixels[Index + 2] = FillColor.R;   // Red
			Pixels[Index + 3] = FillColor.A;   // Alpha
		}
	}

	// 解锁纹理
	OutTexture->PlatformData->Mips[0].BulkData.Unlock();

	// 更新纹理资源
	OutTexture->UpdateResource();

	return true;
}