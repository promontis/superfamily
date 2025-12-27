// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

using UnrealBuildTool;

public class Superfamily : ModuleRules
{
	public Superfamily(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"UMG",
			"CommonUI",
			"CommonInput",
			"Niagara",
			"Paper2D"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"Json",
			"JsonUtilities",
			"HTTP",
			"OnlineSubsystem",
			"OnlineSubsystemUtils"
		});

		// Platform-specific dependencies
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicFrameworks.AddRange(new string[] { "Foundation", "UIKit", "AVFoundation" });
		}

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.Add("Launch");
		}

		// Uncomment when plugins are ready
		// PrivateDependencyModuleNames.Add("EducationSystem");
		// PrivateDependencyModuleNames.Add("RealLifeMissions");
		// PrivateDependencyModuleNames.Add("RNUEBridge");
	}
}
