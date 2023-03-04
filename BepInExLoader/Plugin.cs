using BepInEx;
using BepInEx.Unity.IL2CPP;
using System;
using System.Runtime;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;

namespace DWNOHelper.ManagedLoader;

[BepInPlugin(MyPluginInfo.PLUGIN_GUID, MyPluginInfo.PLUGIN_NAME, MyPluginInfo.PLUGIN_VERSION)]
public class Plugin : BasePlugin
{
	public override void Load()
	{
		try
		{
			string modulePath;
			{
				StringBuilder buffer = new StringBuilder(512);
				GetModuleFileName(Marshal.GetHINSTANCE(this.GetType().Module), buffer, 512);
				modulePath = buffer.ToString();
			}
			string baseDir = Path.GetDirectoryName(modulePath);
			string helperDllPath = Path.Combine(baseDir, "DWNOHelper.dll");

			Log.LogInfo($"Attempting to load library \"{helperDllPath}\"");
			var hmodule = NativeLibrary.Load(helperDllPath);

			// Plugin startup logic
			Log.LogInfo($"Plugin {MyPluginInfo.PLUGIN_GUID} is loaded!");
		}
		catch (Exception e)
		{
			Log.LogError($"Plugin {MyPluginInfo.PLUGIN_GUID} failed to load: {e.Message}");
		}
	}

	[DllImport("Kernel32.dll")]
	static extern uint GetModuleFileName(IntPtr hModule, [Out] StringBuilder lpFilename, [In][MarshalAs(UnmanagedType.U4)] int nSize);
}
