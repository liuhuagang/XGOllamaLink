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
             "$(ModuleDir)/Public/Type",
             "$(ModuleDir)/Public/Subsystem",
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {

                "XGOllamaLink/Public/AsyncAction",
                "XGOllamaLink/Public/Log",
                "XGOllamaLink/Public/Type",
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
				"Engine",
                "Json",
                "JsonUtilities",
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
			);
	}
}
