#if UNITY_ANDROID

using UnityEngine;

public static class MainActivity
{
	#if UNITY_ANDROID && !UNITY_EDITOR
		public static AndroidJavaClass activityClass = new AndroidJavaClass("de.joshuareibert.dontslamyourhead.MainActivity");
		public static AndroidJavaClass unityActivityClass = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		public static AndroidJavaObject activityObj = unityActivityClass.GetStatic<AndroidJavaObject>("currentActivity");
	#else
		public static AndroidJavaClass activityClass;
		public static AndroidJavaClass unityActivityClass;
		public static AndroidJavaObject activityObj;
	#endif

	public static bool CallMethod(string name, params object[] args) {
		if (activityClass == null) {
			Debug.LogError("Object is null when calling method " + name);
			return false;
		}
		try {
			activityClass.Call(name, args);
			return true;
		} catch (AndroidJavaException e) {
			Debug.LogError("Exception calling method " + name + ": " + e);
			return false;
		}
	}
}

#endif
