// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TossPot : ModuleRules
{
	public TossPot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem", "OnlineSubsystemUtils", "AdvancedSessions" });


        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");


        // Uncomment if you are using online features
        PrivateDependencyModuleNames.Add("OnlineSubsystem");
    }
}
