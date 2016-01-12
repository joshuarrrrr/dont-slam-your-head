using UnityEngine;
using System.Collections;

public class Tracking : MonoBehaviour {

	private Vector3 startPosition;

	// Use this for initialization
	void Start () {
		Transform transform = GetComponent<Transform>();
		startPosition = transform.position;
	}

	// Update is called once per frame
	void Update () {
		AndroidJavaObject activityObj = MainActivity.activityObj;
		Vector3 trackingPosition = new Vector3(
			activityObj.Call<float>("getTranslationX"),
			activityObj.Call<float>("getTranslationY"),
			activityObj.Call<float>("getTranslationZ")
			);
		transform.position = startPosition + trackingPosition;
		Debug.Log(transform.position);
	}
}
