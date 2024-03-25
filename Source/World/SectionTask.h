// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SectionTask
{
public:
	SectionTask();


    static void DoWork()
    {
        // 这里是你的任务逻辑，可以是任何需要在后台执行的操作
        // 例如复杂的计算、文件加载、网络请求等等
        // 这里只是一个示例，打印一条信息
        UE_LOG(LogTemp, Warning, TEXT("Task is being executed in background!"));
    }


    ~SectionTask();
};
