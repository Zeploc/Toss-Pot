// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonFunctions.generated.h"

/**
 * 
 */
UCLASS()
class TOSSPOT_API UCommonFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
		//UFUNCTION(BlueprintPure, Category = "Solus Data Singleton")
		//	static class UMythosSingleton* GetMythosSingleton(bool& IsValid);
		
		UFUNCTION(BlueprintPure)
			static bool IsWithEditor();


		UFUNCTION(BlueprintCallable)
			static void AddDebugMessage(FString _Message, bool _Error = false, bool _PrintToConsole = true);
};
