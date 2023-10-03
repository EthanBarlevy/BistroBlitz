// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BistroBlitz : ModuleRules
{
	public BistroBlitz(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		if (Target.Platform == UnrealTargetPlatform.Win64)
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Steam", "lib", "steam_api64.lib"));
		else if (Target.Platform == UnrealTargetPlatform.Linux)
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Steam", "lib", "libsteam_api.so"));

		try
		{
			string SteamDLLFileName = "steam_api64.dll";
			string SteamDLLPath = Path.Combine(ModuleDirectory, "Steam", "lib", SteamDLLFileName);
			string ProjectPath = Directory.GetParent(ModuleDirectory).Parent.ToString();
			string BinariesDir = Path.Combine(ProjectPath, "Binaries", Target.Platform.ToString());

			if (!Directory.Exists(BinariesDir))
				Directory.CreateDirectory(BinariesDir);

			File.Copy(SteamDLLPath, Path.Combine(BinariesDir, SteamDLLFileName), true);
		}
		catch { }
	}
}
