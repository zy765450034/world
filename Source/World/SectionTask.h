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
        // ��������������߼����������κ���Ҫ�ں�ִ̨�еĲ���
        // ���縴�ӵļ��㡢�ļ����ء���������ȵ�
        // ����ֻ��һ��ʾ������ӡһ����Ϣ
        UE_LOG(LogTemp, Warning, TEXT("Task is being executed in background!"));
    }


    ~SectionTask();
};
