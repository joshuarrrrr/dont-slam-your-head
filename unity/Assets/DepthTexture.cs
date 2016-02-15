using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class DepthTexture : MonoBehaviour {

	public int width = 320;
	public int height = 240;

	private Texture2D idepthMap;

	void Start () {
		idepthMap = new Texture2D(width, height, TextureFormat.ARGB32, false);
	}

	void Update() {
		float[] idepth = MainActivity.activityObj.Call<float[]>("getIDepth");

		// set the pixel values
		float min = 0.0F;
		float max = 1.0F;
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				int idx = x + y * width;
				if (idepth[idx] == -1.0) {
					idepthMap.SetPixel(x, height - y, Color.black);
				} else {
					float val = Mathf.Clamp01(
						(idepth[idx] - min) / (max - min)
						);
					Color color = new Color(val, val, val, 1.0F);
					idepthMap.SetPixel(x, height - y, color);
				}
			}

		// Apply all SetPixel calls
		idepthMap.Apply();

		// connect texture to material of GameObject this script is attached to
		GetComponent<RawImage>().texture = idepthMap;
	}
}
