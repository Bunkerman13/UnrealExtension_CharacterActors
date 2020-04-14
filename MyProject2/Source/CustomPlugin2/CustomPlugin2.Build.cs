// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CustomPlugin2 : ModuleRules
{
	public CustomPlugin2(ReadOnlyTargetRules Target) : base(Target)
	{
        // Override UnrealEngineBuildTool to speedup compilation times
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        // INCLUDE WHAT YOU NEED CONVENTION ACTIVATION
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;

        // Engine dependencies
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        // The path for the header files
        PublicIncludePaths.AddRange(new string[] { "CustomPlugin2/Public" });

        // The path for the source files
        PublicIncludePaths.AddRange(new string[] { "CustomPlugin2/Private" });

        /*PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);*/
    }
}
