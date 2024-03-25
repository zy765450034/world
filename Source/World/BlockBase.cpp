// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"

const TArray<FVector3f> GVertices =
{
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

const TArray<uint32> GTriangles =
{
     0, 1, 2, 0, 2, 3,   // Front face
    1, 5, 6, 1, 6, 2,   // Right face
    4, 7, 6, 4, 6, 5,   // Back face
    0, 3, 7, 0, 7, 4,   // Left face
    3, 2, 6, 3, 6, 7,   // Top face
    0, 4, 5, 0, 5, 1    // Bottom face
};

const TArray<FVector2f> GTexCoords =
{
    FVector2f(1, 1),
    FVector2f(1, 0),
    FVector2f(0, 0),
    FVector2f(0, 0),
    FVector2f(1, 1),
    FVector2f(1, 0)
};
const TArray<FVector3f> GTangentXs =
{
    FVector3f(1, 0, 0),
    FVector3f(1, 0, 0),
    FVector3f(1, 0, 0),
    FVector3f(1, 0, 0),
    FVector3f(1, 0, 0),
    FVector3f(1, 0, 0)
};

const TArray<FVector3f> GTangentYs =
{
    FVector3f(0, 1, 0),
    FVector3f(0, 1, 0),
    FVector3f(0, 1, 0),
    FVector3f(0, 1, 0),
    FVector3f(0, 1, 0),
    FVector3f(0, 1, 0)
};

const TArray<FVector3f> GTangentZs =
{
    FVector3f(0, 0, 1),
    FVector3f(0, 0, 1),
    FVector3f(0, 0, 1),
    FVector3f(0, 0, 1),
    FVector3f(0, 1, 0),
    FVector3f(0, 1, 0)
};

BlockBase::BlockBase()
{

}

BlockBase::~BlockBase()
{
}

FName BlockBase::GetName(int32 Id)
{
	FName Name = FName(TEXT("Stone"));
	return Name;
}

void BlockBase::CreateFace(const EBDirection Direction, const FVector Position)
{
    const auto Color = FColor::MakeRandomColor();
    const auto Normal = GetNormal(Direction);

    MeshData.Vertices.Append(GetFaceVertices(Direction, Position));
    MeshData.Triangles.Append(GetFaceTriangles(Direction));
    MeshData.Normals.Append({ Normal, Normal, Normal, Normal });
    MeshData.Colors.Append({ Color, Color, Color, Color });
    MeshData.UV0.Append({ FVector2f(1,1), FVector2f(1,0), FVector2f(0,0), FVector2f(0,1) });

    
}

FVector BlockBase::GetNormal(const EBDirection Direction) const
{
    switch (Direction)
    {
    case EBDirection::Forward: return FVector::ForwardVector;
    case EBDirection::Right: return FVector::RightVector;
    case EBDirection::Back: return FVector::BackwardVector;
    case EBDirection::Left: return FVector::LeftVector;
    case EBDirection::Up: return FVector::UpVector;
    case EBDirection::Down: return FVector::DownVector;
    default: throw std::invalid_argument("Invalid direction");
    }
}

TArray<FVector3f> BlockBase::GetFaceVertices(EBDirection Direction, const FVector Position) const
{
    TArray<FVector3f> Vertices;
    for (int i = 0; i < 4; i++)
    {
       // Vertices.Add(BlockVertexData[BlockTriangleData[i + static_cast<int>(Direction) * 4]] + Position);
        Vertices.Add(GVertices[GTriangles[i + static_cast<int>(Direction) * 4]] + FVector3f(Position.X, Position.Y, Position.Z));
    }

    return Vertices;
}

TArray<uint32> BlockBase::GetFaceTriangles(EBDirection Direction) const
{
    TArray<uint32> Triangles;
    for (size_t i = 0; i < 6; i++)
    {
        Triangles.Add(GTriangles[i + static_cast<int>(Direction) * 6]);
    }
    return Triangles;
}

FVector BlockBase::GetPositionInDirection(const EBDirection Direction, const FVector Position) const
{
    switch (Direction)
    {
    case EBDirection::Forward: return Position + FVector::ForwardVector;
    case EBDirection::Back: return Position + FVector::BackwardVector;
    case EBDirection::Left: return Position + FVector::LeftVector;
    case EBDirection::Right: return Position + FVector::RightVector;
    case EBDirection::Up: return Position + FVector::UpVector;
    case EBDirection::Down: return Position + FVector::DownVector;
    default: throw std::invalid_argument("Invalid direction");
    }
}