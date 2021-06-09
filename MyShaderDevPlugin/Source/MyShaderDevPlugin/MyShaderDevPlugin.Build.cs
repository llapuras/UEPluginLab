using UnrealBuildTool;

public class MyShaderDevPlugin : ModuleRules
{
	public MyShaderDevPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		//// Explicitly stating that we use new build setting defaults (or overwrite them).
		//DefaultBuildSettings = BuildSettingsVersion.V2;

		//// Resetting new defaults for clearity.
		//PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		//ShadowVariableWarningLevel = WarningLevel.Error;
		//bLegacyPublicIncludePaths = false;


		// Public module source dependencies.
		PublicDependencyModuleNames.AddRange(new string[] {

			"Core",
			"RenderCore", // Needed for AddShaderSourceDirectoryMapping & ResetAllShaderSourceDirectoryMappings
			"Projects" // Needed for IPluginManager	
		});

		// Private module source dependencies.
		PrivateDependencyModuleNames.AddRange(new string[] {
		
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
		});
	}
}