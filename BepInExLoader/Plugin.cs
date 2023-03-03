using BepInEx;
using BepInEx.Unity.IL2CPP;
using System.Runtime.InteropServices;

namespace DWNOHelper.ManagedLoader;

[BepInPlugin(MyPluginInfo.PLUGIN_GUID, MyPluginInfo.PLUGIN_NAME, MyPluginInfo.PLUGIN_VERSION)]
public class Plugin : BasePlugin
{
	public override void Load()
	{
		try
		{
			var hmodule = NativeLibrary.Load(@"BepInEx\plugins\DWNOHelper.dll");
			// Plugin startup logic
			Log.LogInfo($"Plugin {MyPluginInfo.PLUGIN_GUID} is loaded!");
		}
		catch (System.Exception e)
		{
			Log.LogInfo($"Plugin {MyPluginInfo.PLUGIN_GUID} failed to load: {e.Message}");
		}
	}
}
