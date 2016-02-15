using UnityEngine;
using System.Collections;

public class BoxCloud : MonoBehaviour {

	public int num = 500;

	private GameObject box = null;

	private GameObject[] cloud;

	void Start () {
		Vector3  scale = Vector3.one * 0.02F;
		box = GameObject.CreatePrimitive(PrimitiveType.Cube);
		box.GetComponent<Transform>().localScale = scale;

		cloud = new GameObject[num];
		for (int i = 0; i < num; ++i) {
			cloud[i] = Instantiate(box);
			// cloud[i] = GameObject.CreatePrimitive(PrimitiveType.Cube);
			cloud[i].GetComponent<Renderer>().enabled = false;
		}
	}

	void Update() {
		float[] points = MainActivity.activityObj.Call<float[]>("getPoints");

		for (int i = 0; i < num; ++i) {
			float x = points[i * 3];
			float y = points[i * 3 + 1];
			float z = points[i * 3 + 2];
			if ((x == 0.0F) && (y == 0.0F) && (z == 0.0F)) {
				cloud[i].GetComponent<Renderer>().enabled = false;
			} else {
				Vector3 pos = new Vector3(x, y, z) +
					GetComponent<Transform>().position;
				Debug.Log(i);
				Debug.Log(pos);
				cloud[i].GetComponent<Transform>().position = pos;
				cloud[i].GetComponent<Renderer>().enabled = true;
			}
		}
	}
}
