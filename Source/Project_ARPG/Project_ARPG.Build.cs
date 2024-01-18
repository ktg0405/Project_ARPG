// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_ARPG : ModuleRules
{
	public Project_ARPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
