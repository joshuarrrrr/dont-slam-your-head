using UnityEngine;
using System.Collections;

public class SLAM : MonoBehaviour {

	private Vector3 startPosition;

	// Use this for initialization
	void Start () {
		Transform transform = GetComponent<Transform>();
		startPosition = transform.position;
	}

	// Update is called once per frame
	void Update () {
		Vector3 trackingPosition = new Vector3(
			MainActivity.activityObj.Call<float>("getTranslationX"),
			MainActivity.activityObj.Call<float>("getTranslationY"),
			MainActivity.activityObj.Call<float>("getTranslationZ")
			);
		transform.position = startPosition + trackingPosition;
		// Debug.Log(transform.position);
	}

	public void Reset() {
		MainActivity.activityObj.Call("resetSLAM");
		Debug.Log("RESET");
	}
}
