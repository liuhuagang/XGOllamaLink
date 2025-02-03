// Copyright 2025 Xiao Gang. All Rights Reserved.

using UnrealBuildTool;

public class XGOllamaLink : ModuleRules
{
	public XGOllamaLink(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
             "$(ModuleDir)/Public/AsyncAction",
             "$(ModuleDir)/Public/Config",
             "$(ModuleDir)/Public/Type",
             "$(ModuleDir)/Public/Type/Version",
             "$(ModuleDir)/Public/Subsystem",
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {

                "XGOllamaLink/Public/AsyncAction",
                "XGOllamaLink/Public/Config",
                "XGOllamaLink/Public/Log",
                "XGOllamaLink/Public/Type",
                "XGOllamaLink/Public/Type/Version",
                "XGOllamaLink/Public/Subsystem",
                "XGOllamaLink/Public/Util"

            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "HTTP",
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
                "DeveloperSettings",
                "Engine",
                "Projects",
                "Json",
                "JsonUtilities",
            }
			);

        //Need to make sure Android has Launch module.
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateIncludePathModuleNames.AddRange(
                new string[] {
                    "Launch"
                }
            );
        }


    }
}
