// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

using UnrealBuildTool;

public class EducationSystem : ModuleRules
{
	public EducationSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UMG",
			"CommonUI"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"Json",
			"JsonUtilities",
			"HTTP"
		});

		// Depend on main game module for types
		PrivateDependencyModuleNames.Add("Superfamily");
	}
}
