// Copyright 2018 Augmented Enterprise, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EvaTTS : ModuleRules
{

    public EvaTTS(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

    }
}
