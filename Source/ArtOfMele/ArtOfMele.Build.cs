// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ArtOfMele : ModuleRules
{
	public ArtOfMele(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UnrealEd" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });


        //Do not refer to it for Editor.h error of Linkage
        //if (UEBuildConfiguration.bBuildEditor)
        //{
        //    PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
        //}

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
