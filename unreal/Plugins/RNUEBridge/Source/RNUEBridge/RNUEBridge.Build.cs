// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

using UnrealBuildTool;

public class RNUEBridge : ModuleRules
{
	public RNUEBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Json",
			"JsonUtilities"
		});

		// Platform-specific native bridge dependencies
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicFrameworks.AddRange(new string[] { "Foundation", "UIKit" });
		}

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.Add("Launch");
		}
	}
}
