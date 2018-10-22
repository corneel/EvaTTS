// Copyright 2018 Augmented Enterprise, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EvaTTSTarget : TargetRules
{
	public EvaTTSTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] {
            "SoundFormat",
            "EvaTTS",
            "Json",
            "JsonUtilities"
        } );
	}
}
