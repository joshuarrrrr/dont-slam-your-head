// #if UNITY_ANDROID

using UnityEngine;
using System.Collections;

public class BoxCloud : MonoBehaviour {

	public int num = 1000;

	private GameObject[] cloud;

	public float boxSize = 0.01F;

	public Material material;

	public Transform head;

	// the unknown scale of the whole point cloud
	public float cloudScale = 1.0F;

	private bool initialRotSet = false;
	private Quaternion initialRot;

	void Start () {
		initialRot = Quaternion.identity;
		initCloud();
	}

	void Update() {
		if (!initialRotSet) {
			var rot = Cardboard.SDK.HeadPose.Orientation;
			if (rot != Quaternion.identity) {
				initialRot = rot;
				initialRotSet = true;
				Debug.Log("initial rotation: " +
					rot.eulerAngles.x.ToString() + " deg x, " +
					rot.eulerAngles.y.ToString() + " deg y, " +
					rot.eulerAngles.z.ToString() + " deg z"
					);
			}
		}

		float[] points = MainActivity.activityObj.Call<float[]>("getPoints");

		for (int i = 0; i < num; ++i) {
			float x = points[i * 3];
			float y = points[i * 3 + 1];
			float z = points[i * 3 + 2];
			if ((x == 0.0F) && (y == 0.0F) && (z == 0.0F)) {
				cloud[i].GetComponent<Renderer>().enabled = false;
			} else {
				Vector3 pos = initialRot * (new Vector3(x, -y, z) * cloudScale);
				cloud[i].GetComponent<Transform>().localPosition = pos;
				float distance = Mathf.Clamp01(
					(cloud[i].GetComponent<Transform>().position -
					head.position).magnitude
					);
				cloud[i].GetComponent<Renderer>().enabled = true;
				cloud[i].GetComponent<Renderer>().material.color =
					Color.Lerp(Color.red, Color.green, distance);
			}
		}
	}

	private void initCloud() {
		cloud = new GameObject[num];
		for (int i = 0; i < num; ++i) {
			cloud[i] = GameObject.CreatePrimitive(PrimitiveType.Cube);
			cloud[i].GetComponent<Transform>().localScale =
				Vector3.one * boxSize;
			cloud[i].GetComponent<Renderer>().enabled = false;
			cloud[i].GetComponent<Renderer>().material = material;
			cloud[i].GetComponent<Transform>().parent =
				this.GetComponent<Transform>();
		}
	}

	public void Reset() {
		initialRotSet = false;
		initCloud();
	}

	public void SetScale(float scale) {
		cloudScale = scale;
	}
}

// #endif
