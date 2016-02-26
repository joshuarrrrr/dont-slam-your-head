using UnityEngine;
using System.Collections;

public class BoxCloud : MonoBehaviour {

	public int num = 500;

	private GameObject[] cloud;

	public Vector3 boxSize = Vector3.one * 0.075F;

	// the unknown scale of the whole point cloud
	public float cloudScale = 5.0F;

	private bool initialRotSet = false;
	private Quaternion initialRot;

	void Start () {
		initCloud();
	}

	void Update() {
		if (!initialRotSet) {
			var rot = Cardboard.SDK.HeadPose.Orientation;
			Debug.Log("initial rotation: " + Quaternion.identity);
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

		Vector3 offset = GetComponent<Transform>().position;

		for (int i = 0; i < num; ++i) {
			float x = points[i * 3];
			float y = points[i * 3 + 1];
			float z = points[i * 3 + 2];
			if ((x == 0.0F) && (y == 0.0F) && (z == 0.0F)) {
				cloud[i].GetComponent<Renderer>().enabled = false;
			} else {
				Vector3 pos = new Vector3(x, y, z) * cloudScale;
				pos = initialRot * pos;
				cloud[i].GetComponent<Transform>().position = pos + offset;
				cloud[i].GetComponent<Renderer>().enabled = true;
			}
		}
	}

	private void initCloud() {
		cloud = new GameObject[num];
		for (int i = 0; i < num; ++i) {
			cloud[i] = GameObject.CreatePrimitive(PrimitiveType.Cube);
			cloud[i].GetComponent<Transform>().localScale = boxSize;
			cloud[i].GetComponent<Renderer>().enabled = false;
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
