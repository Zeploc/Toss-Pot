// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonFunctions.h"

#include "Engine/World.h"
//#include "MythosSingleton.h"

#include "TossPot.h"

#include "Engine/World.h"



//UMythosSingleton* UCommonFunctions::GetMythosSingleton(bool& IsValid)
//{
//	IsValid = false;
//	UMythosSingleton* DataInstance = Cast<UMythosSingleton>(GEngine->GameSingleton);
//
//	if (!DataInstance) return NULL;
//	if (!DataInstance->IsValidLowLevel()) return NULL;
//
//	IsValid = true;
//	return DataInstance;
//}

bool UCommonFunctions::IsWithEditor()
{
	return GIsEditor;
}

void UCommonFunctions::AddDebugMessage(FString _Message, bool _Error, bool _PrintToConsole)
{
	if (_PrintToConsole)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, _Error ? FColor::Red : FColor::Black, _Message);
		}
	}
	if (_Error)
	{
		UE_LOG(LogMythosPartyInit, Warning, TEXT("%s"), *_Message);
	}
	else
	{
		UE_LOG(LogMythosPartyInit, Log, TEXT("%s"), *_Message);
	}
}
