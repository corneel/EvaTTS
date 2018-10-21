// Fill out your copyright notice in the Description page of Project Settings.

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
            "JsonUtilities",
            "Sockets",
            "Networking"
        } );
	}
}
