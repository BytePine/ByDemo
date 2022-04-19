// Copyright Byteyang Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ByDemoEditorTarget : TargetRules
{
	public ByDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ByDemo" } );
	}
}
