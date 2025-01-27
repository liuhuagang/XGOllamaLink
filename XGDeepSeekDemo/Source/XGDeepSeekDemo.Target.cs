// Copyright 2025 Xiao Gang. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class XGDeepSeekDemoTarget : TargetRules
{
	public XGDeepSeekDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("XGDeepSeekDemo");
	}
}
