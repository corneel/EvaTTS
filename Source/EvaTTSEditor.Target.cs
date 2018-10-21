// Fill out your copyright notice in the Description page of Project Settings.

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
            "JsonUtilities",
            "Sockets",
            "Networking"
        } );
	}
}
