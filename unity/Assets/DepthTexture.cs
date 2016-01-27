using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class DepthTexture : MonoBehaviour {

	public int width = 320;
	public int height = 240;

	private Texture2D depthMap;

	void Start () {
		depthMap = new Texture2D(width, height, TextureFormat.ARGB32, false);
	}

	void Update() {
		float[] depth = MainActivity.activityObj.Call<float[]>("getDepth");

		// set the pixel values
		float min = 0.0F;
		float max = 1.0F;
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				int idx = x + y * width;
				if (depth[idx] == -1.0) {
					depthMap.SetPixel(x, height - y, Color.black);
				} else {
					float val = Mathf.Clamp01((depth[idx] - min) / (max - min));
					Color color = new Color(val, val, val, 1.0F);
					depthMap.SetPixel(x, height - y, color);
				}
			}

		// Apply all SetPixel calls
		depthMap.Apply();

		// connect texture to material of GameObject this script is attached to
		GetComponent<RawImage>().texture = depthMap;
	}
}
