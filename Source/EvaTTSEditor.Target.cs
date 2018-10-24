// Copyright 2018 Augmented Enterprise, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EvaTTSEditorTarget : TargetRules
{
	public EvaTTSEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        ExtraModuleNames.AddRange( new string[] {
           "EvaTTS",
            "Json",
            "JsonUtilities"
        } );

    }
}
