// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SuperfamilyEditorTarget : TargetRules
{
	public SuperfamilyEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("Superfamily");
		ExtraModuleNames.Add("SuperfamilyEditor");
	}
}
