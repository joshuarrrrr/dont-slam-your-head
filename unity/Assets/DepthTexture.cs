using UnityEngine;
using System.Collections;

public class DepthTexture : MonoBehaviour {

	private int width = 320;
	private int height = 240;

	private Texture2D texture;

	void Start () {
		texture = new Texture2D(width, height, TextureFormat.ARGB32, false);
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
					texture.SetPixel(x, y, Color.clear);
				} else {
					float val = Mathf.Clamp01((depth[idx] - min) / (max - min));
					Color color = new Color(val, val, val, 1.0F);
					texture.SetPixel(x, y, color);
				}
			}

		// Apply all SetPixel calls
		texture.Apply();

		// connect texture to material of GameObject this script is attached to
		GetComponent<Renderer>().material.mainTexture = texture;
	}
}
