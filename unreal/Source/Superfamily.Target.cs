// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SuperfamilyTarget : TargetRules
{
	public SuperfamilyTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("Superfamily");

		// Mobile optimizations
		bUseLoggingInShipping = false;
		bUseChecksInShipping = false;

		// Enable LTO for shipping builds
		bAllowLTCG = true;
	}
}
